#define UNICODE

#include <Windows.h>
#include <iostream>
#include "handler.h"


Handler::Handler(){
    
}

bool Handler::registerProtocol( string  s_protocol )
{
  //string to wstring
  wstring protocol(s_protocol.length(), L' '); // Make room for characters  
  std::copy(s_protocol.begin(), s_protocol.end(), protocol.begin());

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

  lResult = RegSetValueEx(hKeyCommand, L"" , 0 , REG_SZ , (LPBYTE)(L"todo-chrome extension") , ((( (DWORD)lstrlen(L"todo-chrome extension") + 1)) * 2));
  if ( lResult != ERROR_SUCCESS )
    return false;

  RegCloseKey(hKeyCommand);
  return true;
}

bool Handler::removeProtocol ( string protocol ){
  //TODO
  return false;
}

