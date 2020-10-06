#pragma once
// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 DRIVERCONTROL_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// DRIVERCONTROL_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef DRIVERCONTROL_EXPORTS
#define DRIVERCONTROL_API extern "C" __declspec(dllexport)
#else
#define DRIVERCONTROL_API extern "C" __declspec(dllimport)
#endif




//DRIVERCONTROL_API int fnXHXDriverOperation(void);
/*我的导出************************************************************************/
//所有小浣熊模块导出均以"XHX_"标记开头

//返回是否成功
//加载驱动
DRIVERCONTROL_API BOOL WINAPI XHX_DriverLoad();
//返回是否成功
//检测驱动是否加载成功（因为机器配置不同，建议加载后等待几秒钟，调用此函数检查是否成功）
DRIVERCONTROL_API BOOL WINAPI XHX_CheckDriverIsSuccess();

//卸载驱动
DRIVERCONTROL_API VOID WINAPI XHX_DriverUnload();

//返回是否成功
//读内存
//进程ID（注意，不同于系统api，此处为进程ID）
//地址（64 32不统一）
//数组指针（64 32不统一）
//长度（64 32不统一）
//实际完成长度的引用（为指针或引用类型）（64 32不统一）
DRIVERCONTROL_API BOOL WINAPI XHX_ReadProcessMemory(_In_ DWORD dwProcessId, _In_ LPCVOID lpBaseAddress, _Out_opt_ LPVOID lpBuffer, _In_ SIZE_T nSize, _Out_opt_ SIZE_T* lpNumberOfBytesRead);

//返回是否成功
//写内存
//进程ID（注意，不同于系统api，此处为进程ID）
//地址（64 32不统一）
//数组指针（64 32不统一）
//长度（64 32不统一）
//实际完成长度的引用（为指针或引用类型）（64 32不统一）
DRIVERCONTROL_API BOOL WINAPI XHX_WriteProcessMemory(_In_ DWORD dwProcessId, _In_ LPVOID lpBaseAddress, _In_reads_bytes_(nSize) LPCVOID lpBuffer, _In_ SIZE_T nSize, _Out_opt_ SIZE_T* lpNumberOfBytesWritten);

//按键
//Byte 键盘扫描码（可配合MapVirtualKey使用），弹起间隔ms
DRIVERCONTROL_API VOID WINAPI XHX_KeyClick(_In_ BYTE bScan, _In_ DWORD dwClock);

//点击鼠标左键
//弹起间隔ms
DRIVERCONTROL_API VOID WINAPI XHX_MouseLeftClick(_In_ DWORD dwClock);

//点击鼠标右键
//弹起间隔ms
DRIVERCONTROL_API VOID WINAPI XHX_MouseRightClick(_In_ DWORD dwClock);

//鼠标移动
//x坐标，y坐标
DRIVERCONTROL_API VOID WINAPI XHX_MouseMove(_In_ DWORD dx, _In_ DWORD dy, _In_ DWORD MoveTimeTick);

//删除文件
//文件路径指针
DRIVERCONTROL_API BOOL WINAPI XHX_DeleteFileW(_In_ LPCWSTR lpFileName);

//返回整数
//16进制字串转为数值，支持64位数
//字符串
DRIVERCONTROL_API ULONGLONG WINAPI XHX_HexStringToValue(_In_ LPCSTR lpLibFileName);

//返回整数
//以16进制显示的字符串转为字节数组（文本到字节集）
//字符串
DRIVERCONTROL_API ULONGLONG WINAPI XHX_HexStringToHexArry(_In_ LPCSTR lpStringWithHex, _In_opt_ LPVOID lpBuffer);

//添加进程保护
//进程PID
DRIVERCONTROL_API BOOL WINAPI XHX_AddProtectProcessId(_In_ DWORD dwPid);

//移除进程保护
//进程PID
DRIVERCONTROL_API BOOL WINAPI XHX_RmoveProtectProcessId(_In_ DWORD dwPid);

//移除所有保护进程
//进程PID
DRIVERCONTROL_API BOOL WINAPI XHX_RmoveAllProtectProcess();


//未使用
DRIVERCONTROL_API void WINAPI XHX_____0(_In_ DWORD dwProcessId, _In_ float 倍数);

//未使用
DRIVERCONTROL_API void WINAPI XHX_____1(_In_ DWORD dwProcessId, _In_ float 倍数);

//未使用
DRIVERCONTROL_API void WINAPI XHX_____2(_In_ DWORD dwProcessId, _In_ bool 是否屏蔽);

//返回：成功为地址，失败返回0
//进程pid
// 要分配的内存区域的地址
// 分配的大小
// 分配的类型
// 该内存的初始保护属性
DRIVERCONTROL_API unsigned long long WINAPI XHX_VirtualAlloc(_In_ DWORD dwProcessId, _In_opt_ unsigned long long lpAddress, _In_ SIZE_T dwSize, _In_ DWORD flAllocationType, _In_ DWORD flProtect);

//返回：成功为地址，失败返回0
//进程pid
// 要释放的内存区域的地址
// 释放的大小
// 释放的类型
DRIVERCONTROL_API LPVOID WINAPI XHX_VirtualFree(_In_ DWORD dwProcessId, _In_opt_ unsigned long long lpAddress, _In_ SIZE_T dwSize, _In_ DWORD flFreeType);


// 返回：成功标志
// 进程pid
// 目标地址起始位置
// 大小
// 请求的保护方式
// 保存老的保护方式
DRIVERCONTROL_API BOOL WINAPI XHX_VirtualProtect(_In_ DWORD dwProcessId, _In_  unsigned long long lpAddress, _In_  SIZE_T dwSize, _In_  DWORD flNewProtect, _Out_ PDWORD lpflOldProtect);

//扫描并摘除r3钩子
DRIVERCONTROL_API bool WINAPI XHX_MH_HOOK_Patch(_In_ DWORD dwProcessId);

//键盘扩展，按下按键
//键盘码（扫描码）
DRIVERCONTROL_API VOID WINAPI XHX_Ex_KeyDown(_In_ DWORD VirtualKey);

//键盘扩展，弹起按键
//键盘码（扫描码）
DRIVERCONTROL_API VOID WINAPI XHX_Ex_KeyUp(_In_ DWORD VirtualKey);

//鼠标左键按下
DRIVERCONTROL_API VOID WINAPI XHX_Ex_MouseLeftButtonDown();

//鼠标左键弹起
DRIVERCONTROL_API VOID WINAPI XHX_Ex_MouseLeftButtonUp();

//返回是否成功
//读内存,32程序读取64位内存时使用（兼容模式）
//进程ID（注意，不同于系统api，此处为进程ID）
//地址（长长整）
//数组指针（长长整）
//长度（长长整）
//实际完成长度的引用（为指针或引用类型）（长长整）
DRIVERCONTROL_API BOOL WINAPI XHX_ReadProcessMemory_Ex(
	_In_ unsigned long dwProcessId,
	_In_ unsigned long long lpBaseAddress,
	_Out_opt_ unsigned long lpBuffer,
	_In_ unsigned long nSize,
	_Out_opt_ unsigned long lpNumberOfBytesRead
);

//返回是否成功
//写内存，32程序读取64位内存时使用（兼容模式）
//进程ID（长长整）
//地址（长长整）
//数组指针（长长整）
//长度（长长整）
//实际完成长度的引用（为指针或引用类型）（长长整）
DRIVERCONTROL_API BOOL WINAPI XHX_WriteProcessMemory_Ex(
	_In_ unsigned long dwProcessId,
	_In_ unsigned long long lpBaseAddress,
	_In_reads_bytes_(nSize) unsigned long lpBuffer,
	_In_ unsigned long nSize,
	_Out_opt_ unsigned long lpNumberOfBytesWritten
);

//模块地址
//获取进程模地址
//进程pid
//模块名(宽字符)
DRIVERCONTROL_API ULONGLONG WINAPI XHX_GetMoudleImageAdressW(_In_ DWORD processPID, _In_ LPCWSTR lpMoudleName);

//模块地址
//获取进程模地址
//进程pid
//模块名(窄字符)
DRIVERCONTROL_API ULONGLONG WINAPI XHX_GetMoudleImageAdressA(_In_ DWORD processPID, _In_ LPCSTR lpMoudleName);

//远程过程
//线程id
//执行地址
DRIVERCONTROL_API BOOL WINAPI XHX_RemoteThreadCall(_In_ DWORD threadID, _In_ unsigned long long lpCodeAddress, _In_ bool isWaitForFinished = 0);

//远程过程
//线程id
//执行地址
DRIVERCONTROL_API BOOL WINAPI XHX_RemoteHookCall(_In_ DWORD threadID, _In_ unsigned long long lpHookAdress, _In_ unsigned long long lpCodeAddress, _In_ bool isWaitForFinished = 0);

//远程过程
//进程id
//执行地址
DRIVERCONTROL_API BOOL WINAPI XHX_RemoteHookCall_Ex(_In_ DWORD processID, _In_ unsigned long long lpHookAdress, _In_ unsigned long long qwHookSize, _In_ unsigned long long lpCodeAddress, _In_ bool isWaitForFinished = 0);


//远程HOOK
//进程id
//HOOK地址
//HOOK长度
DRIVERCONTROL_API unsigned long long  WINAPI XHX_RemoteHookSet64(_In_ DWORD processID, _In_ unsigned long long lpHookAdress, _In_ unsigned long long qwHookSize);

//远程过程
//进程id
//执行地址
DRIVERCONTROL_API BOOL WINAPI XHX_RemoteDNFCall(_In_ DWORD processID,_In_ unsigned long long lpCodeAddress, _In_ bool isWaitForFinished = 0);


//远程过程
//线程id
//执行地址
DRIVERCONTROL_API BOOL WINAPI XHX_PatchOD(_In_ DWORD threadID);

//判断进程是否为64进程
//进程id
DRIVERCONTROL_API BOOL WINAPI XHX_IsWin64Process(_In_ DWORD processPID);

//魔法保护
//进程id
DRIVERCONTROL_API BOOL WINAPI XHX_MagicProcessProtect(_In_ DWORD processPID);

//取消魔法保护
DRIVERCONTROL_API BOOL WINAPI XHX_MagicUnProcessProtect();

