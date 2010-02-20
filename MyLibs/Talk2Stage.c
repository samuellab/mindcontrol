// usb_rcfg.cpp : A simple USB DOS console application.
// Author: Doug Lovett
// Birth: 02/07/2000
// Ludl Electronic Products Copyright 2000

/*
 * Compile by running:
 *
 * gcc -v -Wall -o bin/Talk2Stage.exe MyLibs/Talk2Stage.c   -lsetupapi
 *
 */

#include <windows.h>
#include <objbase.h>
#include <setupapi.h> // you may have to manually include this library.
#include <initguid.h>
#include <conio.h>
#include <stdio.h>

// Defines
DEFINE_GUID(LEP_GUID, // LEP's global, unique identifier
		0x4d48f140, 0x44e2, 0x11d3, 0x9d, 0x64, 0x0, 0xe0, 0x29, 0x1d, 0xee, 0x58)
;
#define CTL_CODE( DeviceType, Function, Method, Access ) ( ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method))
#define METHOD_BUFFERED 0
#define FILE_ANY_ACCESS 0
#define FILE_DEVICE_UNKNOWN 0x00000022
#define LEPUSB_IOCTL_VENDOR_INDEX 0x0800
#define IOCTL_LEPUSB_GET_READ_LENGTH CTL_CODE(FILE_DEVICE_UNKNOWN, LEPUSB_IOCTL_VENDOR_INDEX+1,METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_LEPUSB_GET_VERSION_INFO CTL_CODE(FILE_DEVICE_UNKNOWN, LEPUSB_IOCTL_VENDOR_INDEX+2,METHOD_BUFFERED, FILE_ANY_ACCESS)
// Function prototypes
int UsbScan(char*);

// Global Variables



// PrintVersion() - Gets and printf the driver version information.
void PrintVersion(HANDLE hUsb) {
	UCHAR Ver[512];
	ULONG nBytes;
	BOOLEAN Success;
	Success = DeviceIoControl(hUsb, IOCTL_LEPUSB_GET_VERSION_INFO, NULL, 0,
			Ver, sizeof(Ver), &nBytes, NULL);
	if (!Success)
		printf("ERROR: Read Driver Version.\n");
	Ver[nBytes] = NULL; // don't forget the NULL terminator
	printf("%s", Ver); // printf the Version
}
// --------------------------------------------------------------------- //

/*
 * Initializes the USB stage;
 */
HANDLE InitializeUsbStage(){
	char DeviceName[MAX_PATH];

	// Scan for Usb Device
	if (!UsbScan(DeviceName)) {
		printf("No devices found!\n");
		return 0;
	}
	printf("Device Found: %s\n", DeviceName);
	HANDLE hUsb = CreateFile(DeviceName, GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hUsb == INVALID_HANDLE_VALUE) {
		printf("Error %d: Failed to open USB file handle.\n", GetLastError());
		return 0;
	} else
		printf("Device Opened: ");
	// Print driver version
	PrintVersion(hUsb);
	return hUsb;
}

int spinStage(HANDLE s, int xspeed,int yspeed){
	DWORD Length;
	char* buff=(char*) malloc(sizeof(char)*1024);
	sprintf(buff,"SPIN X=%d Y=%d\r",xspeed,yspeed);
	WriteFile(s, buff, strlen(buff), &Length, NULL);
	free(buff);
	return 0;

}

int haltStage(HANDLE s){
		DWORD Length;
		WriteFile(s, "HALT\r", strlen("HALT\r"), &Length, NULL);
		return 0;

}

int moveStageRel(HANDLE s, int xpos, int ypos){
	DWORD Length;
	char* buff=(char*) malloc(sizeof(char)*1024);
	sprintf(buff,"MOVEI X=%d Y=%d\r",xpos,ypos);
	WriteFile(s, buff, strlen(buff), &Length, NULL);
	free(buff);
	return 0;
}


int zeroStage(HANDLE s){
	DWORD Length;
	WriteFile(s, "HERE X=0 Y=0\r", strlen("HERE X=0 Y=0\r"), &Length, NULL);
	return 0;

}

int centerStage(HANDLE s){
	DWORD Length;
	WriteFile(s, "CENTER X=30000 Y=30000\r", strlen("CENTER X=30000 Y=30000\r"), &Length, NULL);
	printf("Centering stage.\n This takes a really really long time.\n");
	printf("Hit enter when done. This will zero the stage.\n");
	scanf("");
	zeroStage(s);
	return 0;

}


void steerStageFromNumberPad(HANDLE s, int speed, int input){
	  switch (input) {
	  /** Cardinal Directions **/
		case 6:
			printf("Right!\n");
			spinStage(s,speed,0);
			break;
		case 8:
			printf("Up!\n");
			spinStage(s,0,speed);
			break;
		case 4:
			printf("Left!\n");
			spinStage(s,-speed,0);
			break;
		case 2:
			printf("Down!\n");
			spinStage(s,0,-speed);
			break;
		/** Multiples of 45 **/
		case 9:
			printf("Up-Right!\n");
			spinStage(s,speed,speed);
			break;
		case 7:
			printf("Up-Left!\n");
			spinStage(s,-speed,speed);
			break;
		case 1:
			printf("Down-Left!\n");
			spinStage(s,-speed,-speed);
			break;
		case 3:
			printf("Down-Right!\n");
			spinStage(s,speed,-speed);
			break;
		case 5:
			printf("HALT!\n");
			haltStage(s);
			break;
		default:
			break;
	  }
	  return;
}


int main() {
	HANDLE hUSB= InitializeUsbStage();
	char Buffer[1024];
	DWORD Length, result;

	int input;


	printf("Uses number pad arrow keys. Hit <enter> to invoke.\n Hit 5 <enter> to stop. Hit 0 <enter> to quit.\n");

	int speed=500;

	while(1){
	  scanf("%d",&input);
	  if (input <10 && input >0){

		  steerStageFromNumberPad(hUSB,speed,input);
	  } else {
		  break;
	  }
	}
		Sleep(1000);
		printf("GoodBye!");
} // end of main()



/*
// ------------------------------------------------------------------------ //
// GetRxLen() - If the parameter passed is zero this function simply returns
// the available data in the USB IN buffer. Else this function waits for the
// charactor given. This work's well for high level commands where a colon(:)
// or linefeed (0x0A) is expected at the end of a incomming transmission.
// For low level mode you should just poll for the length of data that your
// command requires, because in low level command answers are fixed in length.
DWORD GetRxLen(char c) {
	struct _ReadLenStruct {
		union {
			ULONG DataLength;
			char UserChar[sizeof(ULONG)];
		};
		ULONG FreeLength;
		ULONG LFLength;
		ULONG UserLength;
	} ReadLen;
	ULONG nBytes;
	BOOLEAN Success;
	while (1) {
		ReadLen.UserChar[0] = c;
		Success = DeviceIoControl(hUsb, IOCTL_LEPUSB_GET_READ_LENGTH, &ReadLen,
				1, &ReadLen, sizeof(ReadLen), &nBytes, NULL);
		if (!Success || (nBytes != sizeof(ReadLen))) {
			printf("ERROR: Returned from DeviceIoControl.\n");
			CloseHandle(hUsb);
			exit(0);
		}
		if (ReadLen.UserLength || kbhit())
			break;
		if (!c)
			break;
	}
	if (c)
		return (ReadLen.UserLength);
	else
		return (ReadLen.DataLength);
}
*/


// ------------------------------------------------------------------------ //
// UsbScan() - Scan for first USB device with a GUID that matches the one
// passed. Return 1 if device found, else 0.
// This function only detech the first match of the device found.
// If you have more than one controller attached you will have to
// scan for the device more than once. See the MFC windows
// example. You can also get the devicename from the registry.
int UsbScan(char* DeviceName) {



	// Get handle to the devices
	HDEVINFO hInfo = SetupDiGetClassDevs((LPGUID) & LEP_GUID, NULL, NULL,
			DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
	if (hInfo == INVALID_HANDLE_VALUE)
		return (0);
	SP_INTERFACE_DEVICE_DATA Interface_Info;
	Interface_Info.cbSize = sizeof(Interface_Info); // Enumerate device
	if (!SetupDiEnumDeviceInterfaces(hInfo, NULL, (LPGUID) & LEP_GUID, 0,
			&Interface_Info)) {
		SetupDiDestroyDeviceInfoList(hInfo);
		return (0);
	}
	DWORD needed; // get the required length
	SetupDiGetInterfaceDeviceDetail(hInfo, &Interface_Info, NULL, 0, &needed,
			NULL);
	PSP_INTERFACE_DEVICE_DETAIL_DATA detail;
	detail = (PSP_INTERFACE_DEVICE_DETAIL_DATA) malloc(needed);
	if (!detail) {
		SetupDiDestroyDeviceInfoList(hInfo);
		return (0);
	}
	// fill the device details
	detail->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
	if (!SetupDiGetInterfaceDeviceDetail(hInfo, &Interface_Info, detail,
			needed, NULL, NULL)) {
		free((PVOID) detail);
		SetupDiDestroyDeviceInfoList(hInfo);
		return (0);
	}
	strncpy(DeviceName, detail->DevicePath, MAX_PATH);
	free((PVOID) detail);
	SetupDiDestroyDeviceInfoList(hInfo);
	return (1); // return true, USB device found
}
// ---------------------------------------------------------------------- //

