echo
echo genpack
set cs_out_path=./Client\Client\Client\PbMsg
start ./Tool\CodeGenerator\CodeGenerator.exe ./ServerConfig/PbMsg.proto  --output %cs_out_path% --preserve-names
echo succ.
pause.