﻿// Classes and structures being serialized

// Generated by ProtocolBuffer
// - a pure c# code generation implementation of protocol buffers
// Report bugs to: https://silentorbit.com/protobuf/

// DO NOT EDIT
// This file will be overwritten when CodeGenerator is run.
// To make custom modifications, edit the .proto file and add //:external before the message line
// then write the code and the changes in a separate file.
using System;
using System.Collections.Generic;

namespace Protobuf
{
    public partial class CS_PING
    {
        public int ansi_time { get; set; }

        public int id { get; set; }

        public string name { get; set; }

    }

    public partial class SC_PONG
    {
        public int ansi_time { get; set; }

    }

}