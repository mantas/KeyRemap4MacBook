#ifndef BRIDGE_H
#define BRIDGE_H

#include <sys/types.h>
#include <mach/mach_types.h>

// RemapClass initialize_vector format:
//
// base:
// { BRIDGE_REMAPCLASS_INITIALIZE_VECTOR_FORMAT_VERSION, size_of_after, {[<remap>], {<filter>}} }
//
// Example:
//   {
//     BRIDGE_REMAPCLASS_INITIALIZE_VECTOR_FORMAT_VERSION,
//     18,
//     5,BRIDGE_REMAPTYPE_KEYTOKEY,BRIDGE_DATATYPE_KEYCODE,0,BRIDGE_DATATYPE_KEYCODE,11,
//     2,BRIDGE_FILTERTYPE_CONFIG_NOT,881,
//     2,BRIDGE_FILTERTYPE_CONFIG_NOT,882,
//     5,BRIDGE_REMAPTYPE_KEYTOKEY,BRIDGE_DATATYPE_KEYCODE,1,BRIDGE_DATATYPE_KEYCODE,56,
//   };
//
//
//   No remap version
//   {
//     BRIDGE_REMAPCLASS_INITIALIZE_VECTOR_FORMAT_VERSION,
//     0,
//   }
//
// --------------------
//
// <filter>
//   { size_of_after, BRIDGE_FILTERTYPE_XXX, values }
//
// Example of <filter>:
//   { 2,BRIDGE_FILTERTYPE_CONFIG_NOT,881 }
//
// --------------------
//
// <remap>
//   { size_of_after, BRIDGE_REMAPTYPE_XXX, values }
//
// Example of <remap>:
//   { 5,BRIDGE_REMAPTYPE_KEYTOKEY,BRIDGE_DATATYPE_KEYCODE,0,BRIDGE_DATATYPE_KEYCODE,11 };
//
// --------------------

enum {
  // Version 1: initial version
  // Version 2: Added BRIDGE_DATATYPE_DEVICEVENDOR,BRIDGE_DATATYPE_DEVICEPRODUCT,BRIDGE_REMAPTYPE_FORCENUMLOCKON
  // Version 3: Removed some essential configurations. (parameter.statuswindow_alpha_font, ...)
  // Version 4: Added a essential configuration. (general.suppress_growl_warning)

  BRIDGE_REMAPCLASS_INITIALIZE_VECTOR_FORMAT_VERSION = 4,
};

enum {
  BRIDGE_DATATYPE_NONE,
  BRIDGE_DATATYPE_KEYCODE,
  BRIDGE_DATATYPE_MODIFIERFLAG,
  BRIDGE_DATATYPE_FLAGS,
  BRIDGE_DATATYPE_CONSUMERKEYCODE,
  BRIDGE_DATATYPE_POINTINGBUTTON,
  BRIDGE_DATATYPE_KEYBOARDTYPE,
  BRIDGE_DATATYPE_DEVICEVENDOR,
  BRIDGE_DATATYPE_DEVICEPRODUCT,
  BRIDGE_DATATYPE_OPTION,

  BRIDGE_REMAPTYPE_NONE,
  BRIDGE_REMAPTYPE_KEYTOKEY,
  BRIDGE_REMAPTYPE_KEYTOCONSUMER,
  BRIDGE_REMAPTYPE_KEYTOPOINTINGBUTTON,
  BRIDGE_REMAPTYPE_CONSUMERTOCONSUMER,
  BRIDGE_REMAPTYPE_CONSUMERTOKEY,
  BRIDGE_REMAPTYPE_DOUBLEPRESSMODIFIER,
  BRIDGE_REMAPTYPE_DROPKEYAFTERREMAP,
  BRIDGE_REMAPTYPE_DROPPOINTINGRELATIVECURSORMOVE,
  BRIDGE_REMAPTYPE_FORCENUMLOCKON,
  BRIDGE_REMAPTYPE_HOLDINGKEYTOKEY,
  BRIDGE_REMAPTYPE_IGNOREMULTIPLESAMEKEYPRESS,
  BRIDGE_REMAPTYPE_KEYOVERLAIDMODIFIER,
  BRIDGE_REMAPTYPE_POINTINGBUTTONTOKEY,
  BRIDGE_REMAPTYPE_POINTINGBUTTONTOPOINTINGBUTTON,
  BRIDGE_REMAPTYPE_POINTINGRELATIVETOSCROLL,
  BRIDGE_REMAPTYPE_SIMULTANEOUSKEYPRESSES,
  BRIDGE_REMAPTYPE_SETKEYBOARDTYPE,
  BRIDGE_REMAPTYPE_END,

  BRIDGE_FILTERTYPE_NONE,
  BRIDGE_FILTERTYPE_APPLICATION_NOT,
  BRIDGE_FILTERTYPE_APPLICATION_ONLY,
  BRIDGE_FILTERTYPE_CONFIG_NOT,
  BRIDGE_FILTERTYPE_CONFIG_ONLY,
  BRIDGE_FILTERTYPE_MODIFIER_NOT,
  BRIDGE_FILTERTYPE_MODIFIER_ONLY,
  BRIDGE_FILTERTYPE_DEVICE_NOT,
  BRIDGE_FILTERTYPE_DEVICE_ONLY,
  BRIDGE_FILTERTYPE_INPUTMODE_NOT,
  BRIDGE_FILTERTYPE_INPUTMODE_ONLY,
  BRIDGE_FILTERTYPE_INPUTMODEDETAIL_NOT,
  BRIDGE_FILTERTYPE_INPUTMODEDETAIL_ONLY,
  BRIDGE_FILTERTYPE_END,

  BRIDGE_STATUSMESSAGE,
  BRIDGE_VK_CONFIG,
};

enum {
#include "config/output/include.bridge_essential_config_index.hpp"
};

// ------------------------------------------------------------
// UserClient definitions.
enum {
  BRIDGE_USERCLIENT_OPEN,
  BRIDGE_USERCLIENT_CLOSE,
  BRIDGE_USERCLIENT_SYNCHRONIZED_COMMUNICATION,
  BRIDGE_USERCLIENT_NOTIFICATION_FROM_KEXT,
  BRIDGE_USERCLIENT__END__,
};

enum {
  BRIDGE_USERCLIENT_TYPE_NONE,
  BRIDGE_USERCLIENT_TYPE_GET_STATUS_MESSAGE_EXTRA,
  BRIDGE_USERCLIENT_TYPE_GET_STATUS_MESSAGE_MODIFIER,
  BRIDGE_USERCLIENT_TYPE_SET_WORKSPACEDATA,
};

enum {
  BRIDGE_USERCLIENT_NOTIFICATION_TYPE_NONE,
  BRIDGE_USERCLIENT_NOTIFICATION_TYPE_STATUS_MESSAGE_UPDATED,
  BRIDGE_USERCLIENT_NOTIFICATION_TYPE_CHANGE_INPUT_SOURCE,
};

// For BRIDGE_USERCLIENT_NOTIFICATION_TYPE_STATUS_MESSAGE_UPDATED.
enum {
  BRIDGE_USERCLIENT_NOTIFICATION_DATA_STATUS_MESSAGE_NONE,
  BRIDGE_USERCLIENT_NOTIFICATION_DATA_STATUS_MESSAGE_EXTRA,
  BRIDGE_USERCLIENT_NOTIFICATION_DATA_STATUS_MESSAGE_MODIFIER,
  BRIDGE_USERCLIENT_NOTIFICATION_DATA_STATUS_MESSAGE__END__,
};
// BRIDGE_USERCLIENT_NOTIFICATION_TYPE_CHANGE_INPUT_SOURCE uses KeyCode as DATA.

// 64bit alignment.
struct BridgeUserClientStruct {
  uint64_t type;
  mach_vm_address_t data;
  mach_vm_size_t size; // size of data
};
// STATIC_ASSERT for sizeof(struct BridgeUserClientStruct).
// We need to make this value same in kext and userspace.
enum { STATIC_ASSERT__sizeof_BridgeUserClientStruct = 1 / (sizeof(struct BridgeUserClientStruct) == 24) };

struct BridgeWorkSpaceData {
  uint32_t type;
  uint32_t inputmode;
  uint32_t inputmodedetail;
};
enum { STATIC_ASSERT__sizeof_BridgeWorkSpaceData = 1 / (sizeof(struct BridgeWorkSpaceData) == 12) };

#endif
