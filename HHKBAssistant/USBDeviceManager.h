//
//  USBDeviceManager.h
//  HHKBAssistant
//
//  Created by 周 涵 on 2014/05/05.
//  Copyright (c) 2014年 hanks. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <CoreFoundation/CoreFoundation.h>

#include <IOKit/IOKitLib.h>
#include <IOKit/IOMessage.h>
#include <IOKit/IOCFPlugIn.h>
#include <IOKit/usb/IOUSBLib.h>
#include "DataSourceDelegate.h"
#include "XPCManager.h"
#include "Constants.h"
#include "PreferenceUtil.h"

typedef struct MyPrivateData {
    io_object_t				notification;
    IOUSBDeviceInterface	**deviceInterface;
    UInt32					locationID;
    
    // device name
    char                    deviceName[128];
    // additonal point to usb manager, used in device notification method
    void                    *usbManageRef;
} MyPrivateData;

@interface USBDeviceManager : NSObject {

}

// delegate for plist data source
@property (nonatomic, assign) id<DataSourceDelegate>  delegate;
// xpc manager
@property XPCManager *xpcManager;
@property PreferenceUtil *prefUtil;

///////////////////////////////////////////
//// use to listen to usb device
///////////////////////////////////////////
@property IONotificationPortRef	gNotifyPort;
@property io_iterator_t			gAddedIter;
@property CFRunLoopRef			gRunLoop;

- (void) addDeviceNotification:(io_service_t)service messageType:(natural_t)messageType messageArgument:(void *)messageArgument privateDataRef:(MyPrivateData *)privateDataRef;
- (void) detectDeviceAdded:(io_iterator_t) iterator;

// main function to set run loop to listen to usb device
- (int) setupListener;

@end
