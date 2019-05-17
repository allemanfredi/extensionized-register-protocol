#define UNICODE

#include <Windows.h>
#include <string.h>
#include <iostream>
#include <fstream>  
#include <filesystem>
#include "handler.h"

Handler::Handler(){
    
}

bool Handler::registerProtocol( string  s_protocol , string s_extension_id , string s_extension_name )
{
  //string to wstring
  wstring protocol(s_protocol.length(), L' '); // Make room for characters  
  std::copy(s_protocol.begin(), s_protocol.end(), protocol.begin());

  wstring extensionId(s_extension_id.length(), L' ');  
  std::copy(s_extension_id.begin(), s_extension_id.end(), extensionId.begin());

  wstring extensionName(s_extension_name.length(), L' ');  
  std::copy(s_extension_name.begin(), s_extension_name.end(), extensionName.begin());

  // HKEY_CLASSES_ROOT
  //    $PROTOCOL
  //       (Default) = "URL:$NAME"
  //       URL Protocol = ""
  //       shell
  //          open
  //             command
  //                (Default) = "$COMMAND" "%1"
  //
  // However, the "HKEY_CLASSES_ROOT" key can only be written by the
  // Administrator user. So, we instead write to "HKEY_CURRENT_USER\
  // Software\Classes", which is inherited by "HKEY_CLASSES_ROOT"
  // anyway, and can be written by unprivileged users.

  // Main Registry Key
  std::wstring  keyPath = L"Software\\Classes\\";
  keyPath = keyPath + protocol;
  
  std::wstring  url = L"URL:";
  url = url + protocol;

  // Command Key
  std::wstring cmdPath = keyPath + L"\\shell\\open\\command";
  
  HKEY hKey;
  LONG lResult = RegCreateKeyEx(HKEY_CURRENT_USER, keyPath.c_str() , 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
  if ( lResult != ERROR_SUCCESS )
    return false;
  
  lResult = RegSetValueEx(hKey, L"URL Protocol"  , 0 , REG_SZ , (LPBYTE)(L"") , ((((DWORD)lstrlen(L"") + 1)) * 2)); 
  if ( lResult != ERROR_SUCCESS )
    return false;

  lResult = RegSetValueEx(hKey, L"" , 0 , REG_SZ , (LPBYTE)(url.c_str()) , ((( (DWORD)lstrlen(url.c_str()) + 1)) * 2));
  if ( lResult != ERROR_SUCCESS )
    return false;
  RegCloseKey(hKey);
  
  HKEY hKeyCommand;
  lResult = RegCreateKeyEx(HKEY_CURRENT_USER, cmdPath.c_str() , 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKeyCommand, NULL);
  if ( lResult != ERROR_SUCCESS )
    return false;
  
  //devo inserire il path di host.bat
  lResult = RegSetValueEx(hKeyCommand, L"" , 0 , REG_SZ , (LPBYTE)(L"todo-chrome extension") , ((( (DWORD)lstrlen(L"todo-chrome extension") + 1)) * 2));
  if ( lResult != ERROR_SUCCESS )
    return false;

  RegCloseKey(hKeyCommand);

  //enable native messaging
  HKEY hKeyNativeMessagging;
  wstring nativeMessagingPath = L"Software\\Google\\Chrome\\NativeMessagingHosts\\com." + extensionName + L".extension"; 
  lResult = RegCreateKeyEx(HKEY_CURRENT_USER, nativeMessagingPath.c_str() , 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKeyNativeMessagging, NULL);
    if ( lResult != ERROR_SUCCESS )
      return false;

  //create manifest file
  std::ofstream outfile ("./executers/win_manifest.json");
  outfile << "{\n \"name\": \"com."<< s_extension_name << ".extension\",\n \"path\": \"host.bat\",\n \"type\":\"stdio\",\n \"allowed_origins\": [ \"chrome-extension://" + s_extension_id + "/\"]\n}" << std::endl;

  
  //set the manifest path to hKeyNativeMessagging
  char buf[4096];
  GetCurrentDirectoryA(4096, buf);
  string currentDir = std::string(buf);
  string strHostDir = currentDir + "\\executers\\host.bat";
  wstring hostDir(strHostDir.length(), L' '); 
  std::copy(strHostDir.begin(), strHostDir.end(), hostDir.begin());
  
  lResult = RegSetValueEx(hKeyNativeMessagging, L"" , 0 , REG_SZ , (LPBYTE)(hostDir.c_str()) , ((((DWORD)lstrlen(hostDir.c_str()) + 1)) * 2));
  if ( lResult != ERROR_SUCCESS )
    return false;

  return true;
}



bool Handler::removeProtocol ( string protocol ){
  //TODO
  return false;
}

