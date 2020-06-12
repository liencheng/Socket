#!/bin/python
# -*- coding=utf-8 *-*

import sys
import os

#方法模板，
#name为方法名
#body为方法体
class FuncTemplate:
	name = ""
	body = []
	def __init__(self):
		self.name = ""
		self.body = []

#方法类型
class FuncType():
	Raw = 0
	Clean = 1
	OpAssign = 2
	OpEqual = 3
	Get = 4
	Set = 5
	Start = 6
	End = 7
	
#变量模板
class C_Var:
	name = ""
	type = ""
	default_val = ""
	get = False
	set = False

class C_Define:
	c_name = ""
	var_list = []

class C_Template:
	body = {}

def parase_type(shorttype):
	if shorttype == "i":
		return "int"
	if shorttype == "f":
		return "float"
	if shorttype == "i2":
		return "int64"
	return "error_type"
	
def parase_type_default(shorttype):
	if shorttype == "i":
		return "0"
	if shorttype == "f":
		return "0"
	if shorttype == "i2":
		return "0"
	return "error_val"

def parase_func_type(line):
	funtype = FuncType.Raw
	if line.startswith("@f:Clean"):
		funtype = FuncType.Clean
		
	if line.startswith("@f:operate="):
		funtype = FuncType.OpAssign	
		
	if line.startswith("@f:operate=="):
		funtype = FuncType.OpEqual
		
	if line.startswith("@f:Get"):
		funtype = FuncType.Get
		
	if line.startswith("@f:Set"):
		funtype = FuncType.Set

	if line.startswith("@:startclass"):
		funtype = FuncType.Start

	if line.startswith("@:endclass"):
		funtype = FuncType.End
	
	
	
	return funtype
	
def is_fun_end(line):
	if line.find("@end") >= 0:
		return True
	return False
	
def is_comment_line(line):
	if line.startswith("--"):
		return True
	return False

def parase_ini():
	f = open("t_test.ini","r")
	line_data = f.readlines()
	f.close()
	c_temp = C_Define()
	for line in line_data:
		#comment
		line = line.strip()
		if line.startswith("#"):
			continue
		#classname
		if line.startswith("[") and line.endswith("]"):
			c_temp.c_name = line[1:-1]
		#variable
		var_info = line.split(";")
		if len(var_info) >= 2:
			var = C_Var()
			var.name = var_info[0]
			var.type = parase_type(var_info[1])
			var.default_val = parase_type_default(var_info[1])
			if line.find("get") >=0 or line.find("Get") >= 0:
				var.get = True
			if line.find("set")>=0 or line.find("Set")>=0:
				var.set = True
			c_temp.var_list.append(var)
	
	print(c_temp.c_name)
	for var in c_temp.var_list:
		print(var.name)
		print(var.type)
		print(var.default_val)
		print(var.get)
		print(var.set)
	return c_temp

def parase_function_template():
	f = open("template_define.txt", "r")
	line_data = f.readlines()
	f.close()
	bEnterFunc = False
	func_list = []
	func_body = FuncTemplate()
	for line in line_data:
		if line.startswith("@start"):
			bEnterFunc = True
			line_split = line.split(":")
			if len(line_split) >=2:
				func_body.name = line_split[1]
			continue
		if line.startswith("@end"):
			assist_body = FuncTemplate()
			assist_body.name = func_body.name
			for line in func_body.body:
				assist_body.body.append(line)
			func_list.append(assist_body)
			func_body.name = ""
			func_body.body = []
			bEnterFunc = False
		if bEnterFunc == True:
			func_body.body.append(line)
	return func_list

def get_functon_name(line):
	if line.startswith("@function"):
		line_list = line.split(":")
		if len(line_list) >= 2:
			print(line_list[1])
			return line_list[1]
	return ""

def get_function_body(func_name, func_list):
	for func in func_list:
		print(func.name)
		print("p:" + func_name)
		if func.name.strip() == func_name.strip():
			print("equlalllllllllllllllll")
			return func
	return None

#处理单行文本
def process_text(line, define_ini):
	body = []
	line = line.strip()
	line = line.replace("{@classname}",  define_ini.c_name, 10)
	line = line.replace("{@c}", define_ini.c_name, 10)
	split_ret = []
	if line.startswith("{@elem_list}"):
		split_ret = line.split("$")
	if len(split_ret) >= 2:
		sentence = split_ret[1]
		for elem in define_ini.var_list:
			tmp_sentence = sentence.replace("{@elem}", elem.name, 10)
			tmp_sentence = tmp_sentence.replace("{@type}", elem.type, 10)
			tmp_sentence = tmp_sentence.replace("{@elem_default}", elem.default_val, 10)
			body.append(tmp_sentence)
	else:
		body.append(line)
	return body


def process_sentence(line, define_ini, func_list):
	body = []
	#函数声明
	line = line.strip()
	if line.startswith("@function"):
		func_name = get_functon_name(line)
		if len(func_name) >0:
			func = get_function_body(func_name, func_list)
			if func is None:
				print("None")
				return body
			for func_line in func.body:
				line_result = process_text(func_line, define_ini)
				for line_i in line_result:
					body.append(line_i)
		return body
	#文本，处理完输出
	else:
		return process_text(line, define_ini)
	return body

def process_var_decl(var):
	return var.type + " " + var.name + ";"
				
def parase_template_h():
	f = open("template_h.txt","r")
	line_data = f.readlines()
	f.close()
	
	func_list = parase_function_template()
	body = []
	define = parase_ini()
	for line in line_data:
		if is_comment_line(line):
			continue
		l_type = parase_func_type(line)

		if is_fun_end(line):
			continue
		#beforeend,var declare.
		if l_type == FuncType.End:
			body.append("private:")
			for var in define.var_list:
				body.append(process_var_decl(var))
		if l_type > 0:
			continue
		sub_body = process_sentence(line, define, func_list)
		for sub_line in sub_body:
			body.append(sub_line)
	
	fw = open("temp_h.h", "w")
	for line in body:
		print(line)
		fw.write(line)
		fw.write("\n")
		
	fw.close()

parase_template_h()			
		
			
	
	            
