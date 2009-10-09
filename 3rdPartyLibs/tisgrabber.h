#ifndef _TISGRABBER
#define _TISGRABBER

//////////////////////////////////////////////////////////////////////////
/*! @mainpage
	Please see "tisgrabber.h" for the function documentation.
*/


#include "TISGrabberGlobalDefs.h"



// WINAPI for Visual Basic
//#define AC WINAPI

//////////////////////////////////////////////////////////////////////////
/*! Calling convention of the DLL functions. For internal use only. 
*/
#define AC __stdcall ///< __stdcall for Borland C and Ansi C

#ifndef _WINUSER_
//////////////////////////////////////////////////////////////////////////
/*! Workaround if we are in non windows environment.
*/
#define NOHWNDDEFINED 1
#define __HWND int	///< Workaround if we are in non windows environment.
#else
#define __HWND HWND ///<Workaround if we are in windows environment.
#endif

//////////////////////////////////////////////////////////////////////////
/*! This is the handle of an grabber object. Please use the HGRABBER type to access
	this object.
*/
typedef struct HGRABBER_t__ { int unused; } HGRABBER_t; ///<Internal structure of the grabber object handle.

//////////////////////////////////////////////////////////////////////////
/*! The HGRABBER type is used to hold a handle to a grabber object. Each variable of
	HGRABBER type can contain one video capture device. It is possible to create more
	than one variables of this type:
	HGRABBER camera1 = IC_CreateGrabber();
	HGRABBER camera2 = IC_CreateGrabber();
*/
#define	HGRABBER HGRABBER_t* ///< Type of grabber object handle. Used for all functions. 
//////////////////////////////////////////////////////////////////////////
/*! A return value of IC_SUCCESS indicates that a function has been performed
    without an error.
*/
#define IC_SUCCESS   1		///< Return value for success.
//////////////////////////////////////////////////////////////////////////
/*! If a function returns IC_ERROR, then something went wrong.
*/
#define IC_ERROR     0		///< Return value that indicates an error.
//////////////////////////////////////////////////////////////////////////
/*! This error indicates, that an HGRABBER handle has not been created yet. Please
	see IC_CreateGrabber() for creating an HGRABBER handle. 
*/
#define IC_NO_HANDLE -1		///< No device handle. HGRABBER is NULL.
//////////////////////////////////////////////////////////////////////////
/*! This return values indicates that no device has been opened. Please refer to
    IC_OpenVideoCaptureDevice().
*/
#define IC_NO_DEVICE -2     ///< No device opened, but HGRABBER is valid.
//////////////////////////////////////////////////////////////////////////
/*! This return value indicates, that the video capture device is not in live mode,
    but live mode is for the current function call required. Please refer to
	IC_StartLive().
*/
#define IC_NOT_IN_LIVEMODE -3 ///< A device has been opened, but is is not in live mode.

#if defined(__cplusplus)
extern "C"
{
#endif


//////////////////////////////////////////////////////////////////////////
/*! Initialize the ICImagingControl class library. This function must be called
	only once before any other functions of this library are called.
	@param szLicenseKey IC Imaging Control license key or NULL if only a trial version is available.
	@retval IC_SUCCESS on success.
	@retval IC_ERROR on wrong license key or other errors.
	@sa IC_CloseLibrary

*/
int AC IC_InitLibrary( char* szLicenseKey );///<Initialize the library.


//////////////////////////////////////////////////////////////////////////
/*! Creates a new grabber handle and returns it. A new created grabber should be
	release with a call to IC_ReleaseGrabber if it is no longer needed.
	@retval Nonzero on success.
	@retval NULL if an error occurred.
	@sa IC_ReleaseGrabber
*/
HGRABBER AC IC_CreateGrabber();///<Create a new grabber handle


//////////////////////////////////////////////////////////////////////////
/*! Release the grabber object. Must be called, if the calling application
    does no longer need the grabber.
	@param hGrabber The handle to grabber to be released.
	@sa IC_CreateGrabber
*/
void AC IC_ReleaseGrabber( HGRABBER *hGrabber ); ///< Releas an HGRABBER object.

//////////////////////////////////////////////////////////////////////////
/*	Must be called at the of the application to release allocated memory.
	@sa IC_InitLibrary
*/
void AC IC_CloseLibrary(); ///< Closes the library, cleans up memory. 

//////////////////////////////////////////////////////////////////////////
/*! Open a video capture device. The hGrabber handle must have been created previously by
	a call to IC_CreateGrabber(). Once a hGrabber handle has been created it can be
	recycled to open different video capture devices in sequence. 
	@param hGrabber The handle to grabber object, that has been created by a call to IC_CreateGrabber
	@param szDeviceName Friendly name of the video capture device e.g. "DFK 21F04".
	@retval IC_SUCCESS on success.
	@retval IC_ERROR on errors.
	@sa IC_CloseVideoCaptureDevice

	@code
	#include "tisgrabber.h"
	void main()
	{
		HGRABBER hGrabber;
		if( IC_InitLibrary(0) == IC_SUCCESS )
		{
			hGrabber = IC_CreateGrabber();
			if( hGrabber )
			{
				if( IC_OpenVideoCaptureDevice(hGrabber,"DFK 21F04") == IC_SUCCESS )
				{

				// .. do something with the video capture device.

				// Now clean up.
				IC_CloseVideoCaptureDevice( hGrabber );
				IC_ReleaseGrabber( hGrabber );
			}
			IC_CloseLibrary();
		}
	}
	@endcode
*/
int AC IC_OpenVideoCaptureDevice( HGRABBER hGrabber, char *szDeviceName ); ///< Opens a video capture device.


//////////////////////////////////////////////////////////////////////////
/*! Close the current video capture device. The HGRABBER object will not be deleted.
	It can be used again for opening another video capture device.
	@param hGrabber The handle to the grabber object.
*/
void AC IC_CloseVideoCaptureDevice( HGRABBER hGrabber ); ///<Closes a video capture device.

//////////////////////////////////////////////////////////////////////////
/*! Retrieve the name of the current video capture device. If the device is
	invalid, NULL is returned.
	@param hGrabber The handle to the grabber object.
	@retval char* The name of the video capture device
	@retval NULL  If no video capture device is currently opened.
*/
char* AC IC_GetDeviceName(HGRABBER hGrabber ); ///<Returns the name of the current video capture device.

int AC IC_GetVideoFormatWidth( HGRABBER hGrabber); ///<Returns the width of the video format.
int AC IC_GetVideoFormatHeight( HGRABBER hGrabber);///<returns the height of the video format.

//////////////////////////////////////////////////////////////////////////
/*! Set the sink type. A sink type must be set before images can be snapped.
	The sink type basically describes the format of the buffer where the snapped 
	images are stored. 

	Possible values for format are:
	@li Y800	
	@li RGB24
	@li RGB32
	@li UYVY

	The sink type may differ from the currently set video format.

	@param hGrabber The handle to the grabber object.
	@param format The desired color format. Possible values for format are:
		@li Y800	
		@li RGB24
		@li RGB32
		@li UYVY
	@retval IC_SUCCESS on success
	@retval IC_ERROR if something went wrong.

	@note Please note that UYVY can only be used in conjunction with a UYVY video format.


*/
int AC IC_SetFormat( HGRABBER hGrabber, COLORFORMAT format ); ///< Sets the color format of the sink. 


//////////////////////////////////////////////////////////////////////////
/*! Retrieves the format of the sink type currently set (See IC_SetFormat()
	for possible formats). If no sink type is set
	or an error occurred, NONE is returned.
	@param hGrabber The handle to the grabber object.
	@return The current sink color format.
*/
COLORFORMAT AC IC_GetFormat( HGRABBER hGrabber ); ///<Returns the current color format of the sink.


//////////////////////////////////////////////////////////////////////////
/*! Set a video format for the current video capture device. The video format
    must be supported by the current video capture device.
	@param hGrabber The handle to the grabber object.
	@param szFormat A string that contains the desired video format.
	@retval IC_SUCCESS on success
	@retval IC_ERROR if something went wrong.

	@code
	#include "tisgrabber.h"
	void main()
	{
		HGRABBER hGrabber;
		if( IC_InitLibrary(0) == IC_SUCCESS )
		{
			hGrabber = IC_CreateGrabber();
			if( hGrabber )
			{
				if( IC_OpenVideoCaptureDevice(hGrabber,"DFK 21F04") == IC_SUCCESS )
				{
					if( IC_SetVideoFormat(hGrabber,"UYVY (640x480)" == IC_SUCCESS )
					{
						// .. do something with the video capture device.
					}
					// Now clean up.
					IC_CloseVideoCaptureDevice( hGrabber );
					IC_ReleaseGrabber( hGrabber );
				}
				IC_CloseLibrary();
			}
		}
	}
	@endcode
*/
int AC IC_SetVideoFormat( HGRABBER hGrabber, char *szFormat ); ///<Sets the video format.


//////////////////////////////////////////////////////////////////////////
/*! Set a video norm for the current video capture device.
	@note  The current video capture device must support video norms. 
	@param hGrabber The handle to the grabber object.
	@param szNorm A string that contains the desired video format.
	@retval IC_SUCCESS on success
	@retval IC_ERROR if something went wrong.
*/
int AC IC_SetVideoNorm( HGRABBER hGrabber, char *szNorm ); ///<Set the video norm.


//////////////////////////////////////////////////////////////////////////
/*! Set a input channel for the current video capture device. 
	@note  The current video capture device must support input channels.. 
	@param hGrabber The handle to the grabber object.
	@param szChannel A string that contains the desired video format.
	@retval IC_SUCCESS on success
	@retval IC_ERROR if something went wrong.
*/
int AC IC_SetInputChannel( HGRABBER hGrabber, char *szChannel ); ///<Sets an input channel.


//////////////////////////////////////////////////////////////////////////
/*! Start the live video. 
	@param hGrabber The handle to the grabber object.
	@param iShow The parameter indicates:   @li 1 : Show the video	@li 0 : Do not show the video, but deliver frames. (For callbacks etc.)
	@retval IC_SUCCESS on success
	@retval IC_ERROR if something went wrong.
	@sa IC_StopLive
*/
int AC IC_StartLive( HGRABBER hGrabber, int iShow ); ///<Starts the live video.
int AC IC_PrepareLive( HGRABBER hGrabber, int iShow); ///<Prepare the grabber for starting the live video.
int AC IC_SuspendLive(HGRABBER hGrabber); ///<Suspends an image stream and puts it into prepared state. 
 

//////////////////////////////////////////////////////////////////////////
/*! Stop the live video.
	@param hGrabber The handle to the grabber object.
	@sa IC_StartLive
*/
void AC IC_StopLive( HGRABBER hGrabber ); ///<Stops the live video.

int AC IC_IsCameraPropertyAvailable( HGRABBER hGrabber, CAMERA_PROPERTY eProperty ); ///< Check whether a camera property is available.

//////////////////////////////////////////////////////////////////////////
/*! Set a camera property like exposure, zoom.
	
	@param hGrabber The handle to the grabber object.
	@param eProperty The property to be set. It can have following values:
		@li PROP_CAM_PAN	
		@li PROP_CAM_TILT,
		@li PROP_CAM_ROLL,
		@li PROP_CAM_ZOOM,
		@li PROP_CAM_EXPOSURE,
		@li PROP_CAM_IRIS,
		@li PROP_CAM_FOCUS
	@param lValue The value the property is to be set to.
	@retval IC_SUCCESS on success
	@retval IC_ERROR if something went wrong.

	@note  lValue should be in the range of the specified property.
	If the value could not be set (out of range, auto is currently enabled), the
	function returns 0. On success, the functions returns 1.
*/
int AC IC_SetCameraProperty( HGRABBER hGrabber, CAMERA_PROPERTY eProperty, long lValue ); ///< Set a camera property.

int AC IC_CameraPropertyGetRange( HGRABBER hGrabber, CAMERA_PROPERTY eProperty, long *lMin, long *lMax); ///<Get the minimum and maximum value of a camera property
int AC IC_GetCameraProperty( HGRABBER hGrabber, CAMERA_PROPERTY eProperty, long *lValue);  ///< Get a camera property's value.

//////////////////////////////////////////////////////////////////////////
/*! Enable or disable automatic for a camera property. 
	@param hGrabber The handle to the grabber object.
	@param iProperty  The property to be set. It can have following values:
	@li PROP_CAM_PAN	
	@li PROP_CAM_TILT,
	@li PROP_CAM_ROLL,
	@li PROP_CAM_ZOOM,
	@li PROP_CAM_EXPOSURE,
	@li PROP_CAM_IRIS,
	@li PROP_CAM_FOCUS
	@param iOnOFF Enables or disables the automation. Possible values ar
	@li 1 : Enable automatic
	@li 0 : Disable Automatic
	@retval IC_SUCCESS on success
	@retval IC_ERROR if something went wrong.

	@note If the property is not supported by the current video capture device or
	automation of the property is not available with the current video capture
	device, the function returns 0. On success, the function returns 1.
*/
int AC IC_EnableAutoCameraProperty( HGRABBER hGrabber, int iProperty, int iOnOff ); ///<Enables or disables property automation.

int AC IC_IsCameraPropertyAutoAvailable( HGRABBER hGrabber, CAMERA_PROPERTY iProperty ); ///<Check whether automation for a camera property is available.
int AC IC_GetAutoCameraProperty( HGRABBER hGrabber, int iProperty, int *iOnOff ); ///<Retrieve whether automatic is enabled for the specifield camera property.

int AC IC_IsVideoPropertyAvailable( HGRABBER hGrabber, VIDEO_PROPERTY eProperty ); ///<Check whether the specified video property is available. 
int AC IC_VideoPropertyGetRange( HGRABBER hGrabber, VIDEO_PROPERTY eProperty, long *lMin, long *lMax); ///<Retrieve the lower and upper limit of a video property.
int AC IC_GetVideoProperty( HGRABBER hGrabber, VIDEO_PROPERTY eProperty, long *lValue ); ///< Retrieve the the current value of the specified video property.

int AC IC_IsVideoPropertyAutoAvailable( HGRABBER hGrabber, VIDEO_PROPERTY eProperty ); ///<Check whether the specified video property supports automation.
int AC IC_GetAutoVideoProperty( HGRABBER hGrabber, int iProperty, int *iOnOff ); ///<Get the automation state of a video property.
//////////////////////////////////////////////////////////////////////////
/*! Set a video property like brightness, contrast.

	@param hGrabber The handle to the grabber object.
	@param eProperty The property to be set. It can have following values:
	@li PROP_VID_BRIGHTNESS ,
	@li PROP_VID_CONTRAST,
	@li PROP_VID_HUE,
	@li PROP_VID_SATURATION,
	@li PROP_VID_SHARPNESS,
	@li PROP_VID_GAMMA,
	@li PROP_VID_COLORENABLE,
	@li PROP_VID_WHITEBALANCE,
	@li PROP_VID_BLACKLIGHTCOMPENSATION,
	@li PROP_VID_GAIN
	@param lValue The value the property is to be set to.
	@retval IC_SUCCESS on success
	@retval IC_ERROR if something went wrong.

    @note lValue should be in the range of the specified property.
	If the value could not be set (out of range, auto is currently enabled), the
	function returns 0. On success, the functions returns 1.
*/
int AC IC_SetVideoProperty( HGRABBER hGrabber, VIDEO_PROPERTY eProperty, long lValue ); ///<Set a video property.


//////////////////////////////////////////////////////////////////////////
/*! Enable or disable automatic for a video propertery.
	@param hGrabber The handle to the grabber object.
	@param iProperty The property to be set. It can have following values:
	@li PROP_VID_BRIGHTNESS,
	@li PROP_VID_CONTRAST,
	@li PROP_VID_HUE,
	@li PROP_VID_SATURATION,
	@li PROP_VID_SHARPNESS,
	@li PROP_VID_GAMMA,
	@li PROP_VID_COLORENABLE,
	@li PROP_VID_WHITEBALANCE,
	@li PROP_VID_BLACKLIGHTCOMPENSATION,
	@li PROP_VID_GAIN
	@param iOnOFF Enables or disables the automation. Possible values ar
	@li 1 : Enable automatic
	@li 0 : Disable Automatic
	@retval IC_SUCCESS on success
	@retval IC_ERROR if something went wrong.

    @note If the property is not supported by the current video capture device or
	automation of the property is not available with the current video capture
	device, the function reurns 0. On success, the function returns 1.
*/
int AC IC_EnableAutoVideoProperty( HGRABBER hGrabber, int iProperty, int iOnOff ); ///< Switch automatition for a video property,


//////////////////////////////////////////////////////////////////////////
/*! Retrieve the properties of the current video format and sink type 
	@param hGrabber The handle to the grabber object.
	@param *lWidth  This recieves the width of the image buffer.
	@param *lHeight  This recieves the height of the image buffer.
	@param *iBitsPerPixel  This recieves the count of bits per pixel.
	@param *format  This recieves the current color format.
	@retval IC_SUCCESS on success
	@retval IC_ERROR if something went wrong.
*/
int AC IC_GetImageDescription( HGRABBER hGrabber, long *lWidth, long *lHeight, int *iBitsPerPixel, COLORFORMAT *format );///<Retrieve the properties of the current video format and sink typ.


//////////////////////////////////////////////////////////////////////////
/*! Snaps an image. The video capture device must be set to live mode and a 
	sink type has to be set before this call. The format of the snapped images depend on
	the selected sink type. 

	@param hGrabber The handle to the grabber object.
	@param iTimeOutMillisek The Timeout time is passed in milli seconds. A value of -1 indicates, that
							no time out is set.

	
	@retval IC_SUCCESS if an image has been snapped
	@retval IC_ERROR if something went wrong.
	@retval IC_NOT_IN_LIVEMODE if the live video has not been started.

	@sa IC_StartLive 
	@sa IC_SetFormat

*/
int AC IC_SnapImage( HGRABBER hGrabber, int iTimeOutMillisek); ///<Snaps an image from the live stream. 


//////////////////////////////////////////////////////////////////////////
/*! Save the contents of the last snapped image by IC_SnapImage into a file. 
	@param hGrabber The handle to the grabber object.
	@param szFileName String containing the file name to be saved to.
	@param ft File type if the image, It have be
		@li FILETYPE_BMP for bitmap files
		@li FILETYPE_JPEG for JPEG file.
	@param quality If the JPEG format is used, the image quality must be specified in a range from 0 to 100.
	@retval IC_SUCCESS if an image has been snapped
	@retval IC_ERROR if something went wrong.

	@remarks
	The format of the saved images depend on the sink type. If the sink type 
	is set to Y800, the saved image will be an 8 Bit grayscale image. In any
	other case the saved image will be a 24 Bit RGB image.

	@note IC Imaging Control 1.41 only supports FILETYPE_BMP.
	@sa IC_SnapImage
	@sa IC_SetFormat
*/
int AC IC_SaveImage( HGRABBER hGrabber, char *szFileName, IMG_FILETYPE ft, long quality ); ///< Saves an image to a file.


//////////////////////////////////////////////////////////////////////////
/*! Retrieve a byte pointer to the image data (pixel data) of the last snapped
	image (see SnapImage()). If the function fails, the return value is NULL
	otherwise the value is a pointer to the first byte in the lowest image line
	(the image is saved bottom up!).
	@param hGrabber The handle to the grabber object.
	@retval Nonnull Pointer to the image data
	@retval NULL Indicates that an error occurred.
	@sa IC_SnapImage
	@sa IC_SetFormat
*/
unsigned char* AC IC_GetImagePtr( HGRABBER hGrabber ); ///< Retuns a pointer to the image data


//////////////////////////////////////////////////////////////////////////
/*! Assign an Window handle to display the video in.
	@param hGrabber The handle to the grabber object.
	@param hWnd The handle of the window where to display the live video in.
	@retval IC_SUCCESS if an image has been snapped
	@retval IC_ERROR if something went wrong.
*/
int AC IC_SetHWnd( HGRABBER hGrabber, __HWND hWnd ); ///< Sets a window handle for live display


//////////////////////////////////////////////////////////////////////////
/*! Return the serialnumber of the current device. Memory for the serialnumber
    must has been allocated by the application:

	@code
	char szSerial[20];
	GetSerialNumber( hGrabber, szSerial );
	@endcode

	This function decodes the The Imaging Source serialnumbers.
	@param hGrabber The handle to the grabber object.
	@param szSerial char array that recieves the serial number.
*/
void AC IC_GetSerialNumber( HGRABBER hGrabber, char* szSerial );///<Return the video capture device's serial number.


//////////////////////////////////////////////////////////////////////////
/*! Count all connected video capture devices. If the Parameter szDeviceList
    is NULL, only the number of devices is queried. The Parameter szDeviceList
	must be a two dimensional array of char. The iSize parameter specifies the
	length of the strings, that are used in the array.
	
	@param szDeviceList A two dimensional char array that recieves the list. Or NULL if only the count of devices is to be returned.
	@param iSize Not used.
	@retval >= 0 Success, count of found devices
	@retval <0 An error occurred.
	
	Simple sample to list the video capture devices:
	@code
    char szDeviceList[20][40];
	int iDeviceCount;

	iDeviceCount = IC_ListDevices( (char*)szDeviceList,40 );
	for( i = 0; i < iDeviceCount; i++ )
	{
		printf("%2d. %s\n",i+1,szDeviceList[i]);
	}
	@endcode
*/
int AC IC_ListDevices( char *szDeviceList, int iSize );///< Count and list devices.


//////////////////////////////////////////////////////////////////////////
/*! Count all available video formats. If the Parameter szFormatList
    is NULL, only the number of formats is queried. The Parameter szFormatList
	must be a two dimensional array of char. The iSize parameter specifies the
	length of the strings, that are used in the array to store the format names.

	@param hGrabber The handle to the grabber object.
	@param szFormatList A two dimensional char array that recieves the list. Or NULL if only the count of formats is to be returned.

	@retval >= 0 Success, count of found video formats
	@retval <0 An error occurred.
	
	Simple sample to list the video capture devices:
	@code
    char szFormatList[80][40];
	int iFormatCount;
	HGRABBER hGrabber;
	hGrabber = IC_CreateGrabber();
	IC_OpenVideoCaptureDevice(hGrabber, "DFK 21F04" );
	iFormatCount = IC_ListDevices(hGrabber, (char*)szFormatList,40 );
	for( i = 0; i < min( iFormatCount, 80); i++ )
	{
		printf("%2d. %s\n",i+1,szFormatList[i]);
	}
	IC_ReleaseGrabber( hGrabber );
	@endcode
*/
int AC IC_ListVideoFormats( HGRABBER hGrabber, char *szFormatList, int iSize );///<List available video formats.


//////////////////////////////////////////////////////////////////////////
/*! Get the number of the currently available devices. This function creates an
	internal array of all connected video capture devices. With each call to this 
	function, this array is rebuild. The name and the unique name can be retrieved 
	from the internal array using the functions IC_GetDevice() and IC_GetUniqueNamefromList.
	They are usefull for retrieving device names for opening devices.
	
	@retval >= 0 Success, count of found devices.
	@retval <0 An error occurred.

	@sa IC_GetDevice
	@sa IC_GetUniqueNamefromList
*/
int AC IC_GetDeviceCount(); ///<Get the number of the currently available devices. 


//////////////////////////////////////////////////////////////////////////
/*! Get a string representation of a device specified by iIndex. iIndex 
	must be between 0 and IC_GetDeviceCount(). IC_GetDeviceCount() must 
	have been called before this function, otherwise it will always fail.
	
	@param iIndex The number of the device whose name is to be returned. It must be
				  in the range from 0 to IC_GetDeviceCount(),
    @return Returns the string representation of the device on success, NULL
			otherwise.

	@sa IC_GetDeviceCount
	@sa IC_GetUniqueNamefromList
*/
char* AC IC_GetDevice( int iIndex ); ///< Get the name of a video capture device.

//////////////////////////////////////////////////////////////////////////
/*! Get unique device name of a device specified by iIndex. The unique device name
	consist from the device name and its serial number. It allows to differ between 
	more then one device of the same type connected to the computer. The unique device name
	is passed to the function IC_OpenDevByUniqueName

	@param iIndex The number of the device whose name is to be returned. It must be
				in the range from 0 to IC_GetDeviceCount(),
	@return Returns the string representation of the device on success, NULL
				otherwise.

	@sa IC_GetDeviceCount
	@sa IC_GetUniqueNamefromList
	@sa IC_OpenDevByUniqueName
*/
char* AC IC_GetUniqueNamefromList( int iIndex );///< Get the unique name of a video capture device.

//////////////////////////////////////////////////////////////////////////
/*! Get the number of the available input channels for the current device.
    A video	capture device must have been opened before this call.

	@param hGrabber The handle to the grabber object.

	@retval >= 0 Success
	@retval < 0 An error occured.

	@sa IC_GetInputChannel
*/
int AC IC_GetInputChannelCount( HGRABBER hGrabber ); ///<Get the number of the available input channels.


//////////////////////////////////////////////////////////////////////////
/*! Get a string representation of the input channel specified by iIndex. 
	iIndex must be between 0 and IC_GetInputChannelCount().
	IC_GetInputChannelCount() must have been called before this function,
	otherwise it will always fail.		
	@param hGrabber The handle to the grabber object.
	@param iIndex Number of the input channel to be used..

	@retval Nonnull The name of the specified input channel
	@retval NULL An error occured.
	@sa IC_GetInputChannelCount
*/
char* AC IC_GetInputChannel( HGRABBER hGrabber, int iIndex ); ///<Get the name of an input channel.


//////////////////////////////////////////////////////////////////////////
/*! Get the number of the available video norms for the current device. 
	A video capture device must have been opened before this call.
	
	@param hGrabber The handle to the grabber object.

	@retval >= 0 Success
	@retval < 0 An error occured.
	
	@sa IC_GetVideoNorm
*/
int AC IC_GetVideoNormCount( HGRABBER hGrabber ); ///<Get the count of available video norms.


//////////////////////////////////////////////////////////////////////////
/*! Get a string representation of the video norm specified by iIndex. 
	iIndex must be between 0 and IC_GetVideoNormCount().
	IC_GetVideoNormCount() must have been called before this function,
	otherwise it will always fail.		
	
	@param hGrabber The handle to the grabber object.
	@param iIndex Number of the video norm to be used.

	@retval Nonnull The name of the specified video norm.
	@retval NULL An error occured.
	@sa IC_GetVideoNormCount

*/
char* AC IC_GetVideoNorm( HGRABBER hGrabber, int iIndex ); ///<Get the name of a video norm.


//////////////////////////////////////////////////////////////////////////
/*! Get the number of the available video formats for the current device. 
	A video capture device must have been opened before this call.
	
	@param hGrabber The handle to the grabber object.

	@retval >= 0 Success
	@retval < 0 An error occured.

	@sa IC_GetVideoFormat
*/
int AC IC_GetVideoFormatCount( HGRABBER hGrabber ); ///< Returns the count of available video formats.


//////////////////////////////////////////////////////////////////////////
/*! Get a string representation of the video format specified by iIndex. 
	iIndex must be between 0 and IC_GetVideoFormatCount().
	IC_GetVideoFormatCount() must have been called before this function,
	otherwise it will always fail.	

	@param hGrabber The handle to the grabber object.
	@param iIndex Number of the video format to be used.

	@retval Nonnull The name of the specified video format.
	@retval NULL An error occured.
	@sa IC_GetVideoFormatCount
*/
char* AC IC_GetVideoFormat( HGRABBER hGrabber, int iIndex ); ///<Return the name of a video format.



//////////////////////////////////////////////////////////////////////////
/*! Save the state of a video capture device to a file. 
	
	@param hGrabber The handle to the grabber object.
	@param szFileName Name of the file where to save to.

	@retval IC_SUCCESS if an image has been snapped
	@retval IC_ERROR if something went wrong.

	@sa IC_LoadDeviceStateFromFile
*/
int AC IC_SaveDeviceStateToFile(HGRABBER hGrabber, char* szFileName);///<Save the state of a video capture device to a file. 

//////////////////////////////////////////////////////////////////////////
/*! Load a device settings file. On success the device is opened automatically.

	@param hGrabber The handle to the grabber object. If it is NULL then a new HGRABBER handle is
					created. This should be released by a call to IC_ReleaseGrabber when it is no longer needed.
	@param szFileName Name of the file where to save to.

	@return HGRABBER The handle of the grabber object, that contains the new opened video capture device.

	@sa IC_SaveDeviceStateToFile
	@sa IC_ReleaseGrabber
*/
HGRABBER AC IC_LoadDeviceStateFromFile(HGRABBER hGrabber, char* szFileName); ///<Load a device settings file.


//////////////////////////////////////////////////////////////////////////
/*! Save the device settings to a file specified by szFilename. When used 
	with IC Imaging Control 1.41 the device name, the input channel, the 
	video norm and the video format are saved. When used with IC Imaging 
	Control 2.0, the VCDProperties are saved as well. Returns 1 on success,
	0 otherwise.
	Notice that in IC Imaging Control 1.41 the device name includes the trailing 
	number if there is more than one device of the same type available. This can
	cause IC_OpenDeviceBySettings() to fail if one of those devices is unplugged.
	When used with IC Imaging Control 2.0, this cannot happen because the device 
	name is stored without the trailing number. Instead the first device that 
	matches the type specified in the settings file is opened.

	@deprecated Use IC_SaveDeviceStateToFile instead.
	
*/
int AC IC_SaveDeviceSettings( HGRABBER hGrabber, char* szFilename );


//////////////////////////////////////////////////////////////////////////
/*! Open a device by a settings file specified by szFilename. If succedeed,
	1 is returned and a device specified in the settings file is opened and
	initialized with the settings data. If failed, 0 is returned. 

	@deprecated Use IC_LoadDeviceStateFromFile instead.
*/
int AC IC_OpenDeviceBySettings( HGRABBER hGrabber, char* szFilename );


//////////////////////////////////////////////////////////////////////////
/*! Load device settings from a file specified by szFilename. A device must 
	have been opened before this function is called. A check is performed whether
	the current device matches the device type stored in the settings file.
	If so, the settings are loaded and set.
	Returns 1 on success, 0 otherwise.
	Notice: This function will only work with IC Imaging Control 2.0. When used
	with IC Imaging Control 1.41, it will always return 0.

	@deprecated Use IC_LoadDeviceStateFromFile instead.
*/
int AC IC_LoadDeviceSettings( HGRABBER hGrabber, char* szFilename );

//////////////////////////////////////////////////////////////////////////
/*! Open a video capture by using its DisplayName. 
	@param hGrabber The handle to the grabber object.
	@param szDisplayname Displayname of the device. Can be retrieved by a call to IC_GetDisplayName().

	@retval IC_SUCCESS if an image has been snapped
	@retval IC_ERROR if something went wrong.

	@sa IC_GetDisplayName
*/
int AC IC_OpenDevByDisplayName( HGRABBER hGrabber, char *szDisplayname); ///<Open a video capture by using its DisplayName. 

//////////////////////////////////////////////////////////////////////////
/*! Get a DisplayName from a currently open device. The display name of a
	device can be another on different computer for the same video capture
	device. 
	
	@param hGrabber       Handle to a grabber object
	@param szDisplayName  Memory that will take the display name. If it is NULL, the
						  length of the display name will be returned.
	@param iLen           Size in Bytes of the memory allocated by szDisplayName.

	
	@retval IC_SUCCESS     On success. szDisplayName contains the display name of the device.
	@retval IC_ERROR	   iLen is less than the length of the retrieved display name. 
	@retval IC_NO_HANDLE   hGrabber is not a valid handle. GetGrabber was not called.
	@retval IC_NO_DEVICE   No device opened. Open a device, before this function can be used.
	@retval >1             Length of the display name, if szDisplayName is NULL.

	@sa IC_OpenDevByDisplayName
	@sa IC_ReleaseGrabber

*/
int AC IC_GetDisplayName( HGRABBER hGrabber, char *szDisplayname, int iLen); ///<Get the display name of a device.


//////////////////////////////////////////////////////////////////////////
/*! Open a video capture by using its UniqueName. Use IC_GetUniqueName() to
    retrieve the unique name of a camera.

	@param hGrabber       Handle to a grabber object
	@param szDisplayName  Memory that will take the display name.

	@sa IC_GetUniqueName
	@sa IC_ReleaseGrabber

*/
int AC IC_OpenDevByUniqueName( HGRABBER hGrabber, char *szDisplayname);


//////////////////////////////////////////////////////////////////////////
/*! Get a UniqueName from a currently open device.
	
	@param hGrabber      Handle to a grabber object
	@param szUniqueName  Memory that will take the Unique name. If it is NULL, the
						 length of the Unique name will be returned.
	@param iLen          Size in Bytes of the memory allocated by szUniqueName.

	
	@retval IC_SUCCESS    On success. szUniqueName contains the Unique name of the device.
	@retval IC_ERROR	  iLen is less than the length of the retrieved Unique name. 
	@retval IC_NO_HANDLE  hGrabber is not a valid handle. GetGrabber was not called.
	@retval IC_NO_DEVICE  No device opened. Open a device, before this function can be used.
	@retval >1            Length of the Unique name, if szUniqueName is NULL.
	
*/
int AC IC_GetUniqueName( HGRABBER hGrabber, char *szUniquename, int iLen); ///<Get a UniqueName from a currently open device.

//////////////////////////////////////////////////////////////////////////
/*! This returns 1, if a valid device has been opened, otherwise it is 0.

	@param hGrabber      Handle to a grabber object.

	@retval 0 There is no valid video capture device opened
	@retval 1 There is a valid video capture device openend.
*/
int AC IC_IsDevValid( HGRABBER hGrabber); ///<Returns whether a video capture device is valid.


//////////////////////////////////////////////////////////////////////////
/*! Show the VCDProperty dialog. 

	@param hGrabber      Handle to a grabber object.
	@retval IC_SUCCESS on success
	@retval IC_ERROR on error.

	@note This function will only work with IC Imaging Control 2.0 or higher. When used
	with IC Imaging Control 1.41, it will always return 0.
*/
int AC IC_ShowPropertyDialog( HGRABBER hGrabber ); ///<Show the VCDProperty dialog. 


//////////////////////////////////////////////////////////////////////////
/*! Show the device selection dialog. This dialogs enables to select the 
	video capture device, the video norm, video format, input channel and
	frame rate.

	@param hGrabber      Handle to a grabber object.

	@return The passed hGrabber object or a new created if hGrabber was NULL.

	@code
    HGRABBER hTheGrabber;
	hTheGrabber = IC_ShowDeviceSelectionDialog( NULL );
	if( hTheGrabber != NULL )
	{
		IC_StartLive( hTheGrabber, 1 ); // Show the live video of this grabber
		IC_ShowPropertyDialog( hTheGrabber );	// Show the property page of this grabber
	}
	@endcode
*/
HGRABBER AC IC_ShowDeviceSelectionDialog( HGRABBER hGrabber ); ///<Show the device selection dialog.

//////////////////////////////////////////////////////////////////////////
/*!	
	Return whether the current video capture device supports an external 
	trigger. 

	@param hGrabber      Handle to a grabber object.
	@retval 1 An external trigger is supported
	@retval 0 No external trigger is supported.

	@sa IC_EnableTrigger
*/
int AC IC_IsTriggerAvailable( HGRABBER hGrabber ); ///<Check for external trigger support.


//////////////////////////////////////////////////////////////////////////
/*!	Enable or disable the external trigger. 
	@param hGrabber      Handle to a grabber object.
	@param iEnable 1 = enable the trigger, 0 = disable the trigger

	@retval IC_SUCCESS    On success. 
	@retval IC_ERROR	  An error occurred. 

	@sa IC_IsTriggerAvailable
*/
int AC IC_EnableTrigger( HGRABBER hGrabber, int iEnable ); ///<Enable or disable the external trigger. 

//////////////////////////////////////////////////////////////////////////
/*!	Enable or disable the overlay bitmap on the live video
	@param hGrabber      Handle to a grabber object.
	@param iEnable = 1 enables the overlay, 0 disables the overlay.
*/
void AC IC_EnableOverlay( HGRABBER hGrabber, int iEnable ); ///<Enable or disable the overlay bitmap.

//////////////////////////////////////////////////////////////////////////
/*!  BeginPaint returns an HDC for GDI painting purposes (like TextOut() etc.)
	When the paintings are finished, the function IC_EndPaint must be called.

	@param hGrabber      Handle to a grabber object.

	@return HDC The function returns not NULL, if the HDC could be retrieved. If the HDC 
			could not be retrieved or an error has occured, the function returns 0.

	Sample code:
	@code
	HDC hPaintDC;
	hPaintDC = IC_BeginPaint(hGrabber);
	if( hPaintDC != NULL )
	{
	    TextOut( hPaintDC,10,10,"Text",4);
	}
	IC_EndPaint(hGrabber)
	@endcode

	@sa IC_EndPaint
*/
long AC IC_BeginPaint( HGRABBER hGrabber ); ///< BeginPaint returns an HDC for GDI painting purposes.

//////////////////////////////////////////////////////////////////////////
/*!  The EndPaint functions must be called, after BeginPaint has been called,
    and the painting operations have been finished.
	@param hGrabber      Handle to a grabber object.
	@sa IC_BeginPaint
*/
void AC IC_EndPaint( HGRABBER hGrabber ); ///< End painting functions on the overlay bitmap.
//////////////////////////////////////////////////////////////////////////
/*! Display a windows messagebox.
	@param szText Message text
	@param zsTitle Title of the messagebox.
*/
void AC IC_MsgBox( char * szText, char* szTitle ); ///<Display a windows messagebox.


//////////////////////////////////////////////////////////////////////////
/*! Type declaration for the frame ready call back function. 
	@sa IC_SetFrameReadyCallback
*/
typedef void (*FRAME_READY_CALLBACK)
	(HGRABBER hGrabber, unsigned char* pData, unsigned long frameNumber, void* );


//////////////////////////////////////////////////////////////////////////
/*!	Enable frame ready callback.
	@param hGrabber      Handle to a grabber object.
	@param cb Callback function of type FRAME_READY_CALLBACK
	@param x1_argument_in_void_userdata Pointer to some userdata.

	@sa FRAME_READY_CALLBACK
*/
int AC IC_SetFrameReadyCallback(
	HGRABBER				hGrabber,
	FRAME_READY_CALLBACK	cb,
	void*					x1_argument_in_void_userdata);

/////////////////////////////////////////////////////////////////////////
/*!	Set Continuous mode
 
 	In continuous mode, the callback is called for each frame,
 	so that there is no need to use IC_SnapImage etc.
 
	@param hGrabber      Handle to a grabber object.
	@param cont			0 : Snap continouos, 1 : do not automatically snap.

	@remarks
 	Not available in live mode.
 
 */
int AC IC_SetContinuousMode( HGRABBER hGrabber, int cont ); ///<Set Continuous mode.


//////////////////////////////////////////////////////////////////////////
/*! SignalDetected

	Detects whether a video signal is available.

	@param hGrabber      Handle to a grabber object.

	@retval IC_SUCCESS   Signal detected
	@retval IC_ERROR  No video signal detected
	@retval IC_NO_HANDLE  Invalid grabber handle
	@retval IC_NO_DEVICE    No video capture device opened
	@retval IC_NOT_IN_LIVEMODE  No live mode, startlive was not called
*/
int AC IC_SignalDetected( HGRABBER hGrabber  ); ///<Detects whether a video signal is available.


//////////////////////////////////////////////////////////////////////////
/*! Get trigger modes.
	Simple sample to list the video capture devices:

	@param hGrabber      Handle to a grabber object.
	@param szModeList	Twodimensional array of char that will recieve the mode list.
	@param iSze			Size of the array (first dimension)

	@retval 0 : No trigger modes available
	@retval >0 : Count of available trigger modes
	@retval IC_ERROR  No video signal detected
	@retval IC_NO_HANDLE  Invalid grabber handle
	@retval IC_NO_DEVICE    No video capture device opened

	@code
    char szModes[20][10];
	int iModeCount;

	iModeCount = IC_GetTriggerModes(hGrabber, (char*)szModes,20);
	for( int i = 0; i < min( iModeCount, 20); i++ )
	{
		printf("%2d. %s\n",i+1,szModes[i]);
	}
	@endcode
*/
int AC IC_GetTriggerModes( HGRABBER hGrabber,  char *szModeList, int iSize  ); ///<Get trigger modes.


//////////////////////////////////////////////////////////////////////////
/*!  Set the trigger mode.
	Sets the mode that has been retrieved  by a call to IC_GetTriggerModes.

	@param hGrabber	Handle to a grabber object.
	@param szMode	String containing the name of the mode.	

	@retval IC_SUCCESS		Success.
	@retval IC_ERROR		An error occurred
	@retval IC_NO_HANDLE	Invalid grabber handle
	@retval IC_NO_DEVICE    No video capture device opened

*/
int AC IC_SetTriggerMode( HGRABBER hGrabber, char* szMode  ); ///<Set the trigger mode.

//////////////////////////////////////////////////////////////////////////
/*! Set the trigger polarity
	
	Sample:
	@code
	IC_SetTriggerPolarity(hGrabber, 0);
	@endcode
	or
	@code
	IC_SetTriggerPolarity(hGrabber, 1);
	@endcode
	@param hGrabber	Handle to a grabber object.
	@param iPolarity 
		@li 0 : Polarity on direction
		@li 1 : Polarity the other direction

	@retval 0 : No trigger polarity available
	@retval 1 : Count of available trigger modes
	@retval IC_NO_HANDLE	Invalid grabber handle
	@retval IC_NO_DEVICE    No video capture device opened
*/
int AC IC_SetTriggerPolarity( HGRABBER hGrabber, int iPolarity ); ///< Set the trigger polarity.

int AC IC_GetExpRegValRange( HGRABBER hGrabber, long *lMin, long *lMax ); ///< Retrieve exposure register values lower and upper limits.
int AC IC_GetExpRegVal( HGRABBER hGrabber, long *lValue ); ///< Retrieve the current register value of exposure.
int AC IC_SetExpRegVal( HGRABBER hGrabber, long lValue ); ///<Set a register value for exposure.
int AC IC_EnableExpRegValAuto( HGRABBER hGrabber, int iOnOff ); ///<Enable or disable automatic of exposure.
int AC IC_GetExpRegValAuto( HGRABBER hGrabber, int *iOnOff );///<Check whether automatic exposure is enabled.



//////////////////////////////////////////////////////////////////////////
/*! Funktions for the absolute values interface of exposure.
*/
int AC IC_IsExpAbsValAvailable( HGRABBER hGrabber);
int AC IC_GetExpAbsValRange(HGRABBER hGrabber, float *fMin, float *fMax);
int AC IC_GetExpAbsVal(HGRABBER hGrabber, float *fValue);
int AC IC_SetExpAbsVal(HGRABBER hGrabber,  float fValue );




#if defined(__cplusplus)
}
#endif 

#endif
