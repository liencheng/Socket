echo off
echo genpack
set cpp_out_path=GameTool/GameTool/Packet
start ./Tool\protoc-3.11.4-win64\bin\protoc.exe -I=%cd%/ServerConfig/  --cpp_out=%cd%/%cpp_out_path%  PbMsg.proto
echo succ.
pause.