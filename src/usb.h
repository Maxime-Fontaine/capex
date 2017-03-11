// -----------------------------------------------------------------------------
// USB CLASS FOR MANIPULATING DEVICES
// -----------------------------------------------------------------------------
// CONTRIBUTORS : MAXIME FONTAINE
// VERSION : 1.0
// DATE : 20/11/2016
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#ifndef _MXMUSB_H
#define _MXMUSB_H

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <libusb.h>
#include <vector>
#include <string>

#include <usb_status.h>

#ifndef MXM_CALL
    #define MXM_CALL
#endif

namespace mxm
{

	struct DeviceLibUSB
	{
		libusb_device_handle *handle;
		libusb_device *device;
	};


	struct DeviceUSB
	{
		unsigned short PID;
		unsigned short VID;
		unsigned short USBVersion;
		unsigned short DeviceClass;
		std::string Manufacturer;
		std::string Product;
		std::string SerialNumber;
	 	DeviceLibUSB lib;
	};


  	// -----------------------------------------------------------------------------
	//                             USB DECLARATION
	// -----------------------------------------------------------------------------
	//!
	//! \brief A class to manipulate USB Devices (based on libusb-1.0)

	class usb
	{
		public:     // Public methods

			// ---------------------------------------------------------------------
			//! \brief Creates an empty USB class
			//!
			//! This creator creates a USB class. No device is connected to the
			//! class with this constructor
			//!
			// ---------------------------------------------------------------------
			MXM_CALL usb();

			// ---------------------------------------------------------------------
			//! \brief Creates a USB class and connect to device with the
			//! corresponding VID PID.
			//! \param  VID	Vendor Integer of the Device
			//! \param  PID Product Integer of the Device
			//!
			//! This creator creates a USB class and looking for devices with
			//! the coresponding VID PID. If one (and only one) device is found,
			//! the constructor coonects automatically to this device
			//!
			// ---------------------------------------------------------------------
			MXM_CALL usb(int VID, int PID);

			// ---------------------------------------------------------------------
			//! \brief Deletes the USB class and deconnect the device if connected
			//!
			//! This destructor deletes the USB class and deconnects from the
			//! USB device
			//!
			// ---------------------------------------------------------------------
			MXM_CALL ~usb();

			std::vector<DeviceUSB> MXM_CALL FoundDevices(int VID=-1, int PID=-1);

			// ---------------------------------------------------------------------
			//! \brief Connects a USB device to the class
			//! \param device		the device to connect
			//! \param interface	the interface to use (0 by default)
			//! \return	an integer indicating the connection status
			//!
			//! This fucntion connects a USB device to the class.
			//! It returns an integer represnting the status of the connection
			//!
			// ---------------------------------------------------------------------
			int MXM_CALL Open(DeviceUSB device, int interface=0);


			// ---------------------------------------------------------------------
			//! \brief Disconnects a USB device from the class
			//!
			//! This fucntion close the connection of USB device from the class.
			//!
			// ---------------------------------------------------------------------
			void MXM_CALL Close();

			// ---------------------------------------------------------------------
			//! \brief Tests if a USB device is connected to the class
			//! \return	a boolean indicating the connected status
			//!
			//! This fucntion tests if a USB device is connected to the class.
			//! It returns true if a device is connected and false otherwise
			//!
			// ---------------------------------------------------------------------
			bool MXM_CALL IsConnected();

			// ---------------------------------------------------------------------
			//! \brief Gets the VID of the connected USB device
			//! \return	an integer represnting the VID of the USB device
			//!
			//! This accessor gets the VID of the USB device. A device has to
			//! be connected
			//!
			// ---------------------------------------------------------------------
			int MXM_CALL GetVID();

			// ---------------------------------------------------------------------
			//! \brief Gets the PID of the connected USB device
			//! \return	an integer represnting the PID of the USB device
			//!
			//! This accessor gets the PID of the USB device. A device has to
			//! be connected
			//!
			// ---------------------------------------------------------------------
			int MXM_CALL GetPID();

			// ---------------------------------------------------------------------
			//! \brief Gets the USB version of the connected USB device
			//! \return	a string representing the version of the USB protocol
			//!
			//! This accessor gets the USB version of the protocol used by the
			//! USB device. A device has to be connected
			//!
			// ---------------------------------------------------------------------
			std::string MXM_CALL GetUsbVersion();

			// ---------------------------------------------------------------------
			//! \brief Gets the manufacturer of the connected USB device
			//! \return	a string representing the manufactuer of the device
			//!
			//! This accessor gets the manufacturer of the USB device. A device
			//! has to be connected
			//!
			// ---------------------------------------------------------------------
			std::string MXM_CALL GetManufacturer();

			// ---------------------------------------------------------------------
			//! \brief Gets the product of the connected USB device
			//! \return	a string representing the product of the device
			//!
			//! This accessor gets the product of the USB device. A device
			//! has to be connected
			//!
			// ---------------------------------------------------------------------
			std::string MXM_CALL GetProduct();

			// ---------------------------------------------------------------------
			//! \brief Gets the serial number of the connected USB device
			//! \return	a string representing the serial number of the device
			//!
			//! This accessor gets the serial number of the USB device. A device
			//! has to be connected
			//!
			// ---------------------------------------------------------------------
			std::string MXM_CALL GetSerialNumber();
			
			// ---------------------------------------------------------------------
			//! \brief Return a string message for a given status
			//! \param Status	value of the status to convert into string
			//! \return	a string representing the status message
			//!
			//! This method returns a string message corresponding to the status
			//! given in parameter. If no status is given, the last status is used
			//!
			// ---------------------------------------------------------------------
			std::string MXM_CALL GetErrorMessage(int Status=-1);
			
			// ---------------------------------------------------------------------
			//! \brief Write data to the USB Device via EndPoint 0
			//! \param Request	Byte corresponding to the request to send
			//! \param Data		Pointer of bytes containing data to send
			//! \param Length	Nomber of bytes to send
			//! \return	an integer representing the writing status
			//!
			//! This method sends data to the USB device via the End Point 0
			//!
			// ---------------------------------------------------------------------
			int MXM_CALL EP0Write(unsigned char Request, unsigned short Value, unsigned short Index, unsigned char *Data, unsigned long Length);
			
			// ---------------------------------------------------------------------
			//! \brief Read data from the USB Device via EndPoint 0
			//! \param Request	Byte corresponding to the request to send
			//! \param Data		Pointer of bytes containing the returned data
			//! \param Length	Nomber of returned bytes
			//! \return	an integer representing the reading status
			//!
			//! This method gets data from the USB device via the End Point 0
			//!
			// ---------------------------------------------------------------------
			int MXM_CALL EP0Read(unsigned char Request, unsigned short Value, unsigned short Index, unsigned char *Data, unsigned long Length);

		public:     // Public attributs


		private:    // Private methods


		private:    // Private attributs

			//! \brief status returned by libusb funtions
			int status;

			//! \brief opened session of libusb
			libusb_context *session;

			//! \brief Vector of USB devices
			std::vector<DeviceUSB> devices;

			//! \brief Device handle used by libusb
			libusb_device_handle *handle;

			//! \brief Boolean indicating if a USB device is connected
			bool connected;

			//! \brief USB device connected to the class
			DeviceUSB device;

	};

}

#endif
