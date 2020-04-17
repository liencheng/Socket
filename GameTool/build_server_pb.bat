echo
echo genpack
set cpp_out_path=GameTool/GameTool/Packet
start ./Tool/protobuf/protoc.exe --proto_path=./ServerConfig  --cpp_out=%cd%/%cpp_out_path%  ./ServerConfig/PbMsg.proto
echo succ.
pause.