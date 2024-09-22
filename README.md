# HIVIEW
> A multi-process software framework for hisilicon (海思) ipc/dvr/nvr/ebox 
>
> [!important]
> This branch is specifically update for MPP-3559

## Features

- BSP   :  Eth/WiFi/Vpn/Upgrade/Sadp
- MPP   :  Hi3516x/Hi3519x/Hi3559x/Hi3536x
- CODEC :  H264/H265/MJPEG/AAC/PCMA/PCMU
- RTSPS :  Server/Client/Push
- WEBS  :  Http/Https/Websocket/Webrtc
- APP   :  NVR/GUI
- REC   :  fMP4
- RTMPS :  Push
- SIPS  :  UAS/GB28181
- ONVIF :  NVT/NVC
- SRTS  :  SRT/UDP/RTP/SRTP
- SVP   :  YOLO/LPR
- UVC   :  H264/MJPEG

<img src="./res/diagram.jpg" height="150px" />
<img src="./res/webrtc.png" height="150px" />

## source tree
```
.  
├── bin         (output bin)  
├── build       (build config)  
├── fw          (framework)  
│   ├── cfifo   (cycle buffer)  
│   ├── nm      (netmsg)  
│   ├── cjson   (cjson)  
│   └── comm    (comm)  
├── inc         (top include)  
├── lib         (output library)  
└── mod         (module)  
    ├── bsp     (sys init && netinf && syscfg && log)  
    ├── codec   (isp&&venc&vdec&vo)  
    ├── svp     (smart vison platform)  
    ├── rec     (video file to storage)  
    ├── user1   (user custom module)
    ├── mpp     (hisi mpp)  
    ├── app     (application && gui)
    ├── onvif   (onvif nvt && nvc)  
    ├── rtsps   (rtsp server && client)
    └── webs    (web server)  
  
  
// system structure:  
  
+------------+    +------------+         +-----------+  
|    app     |    |   user1    |         |    svp    |             req +------------+
+------------+    +------------+         +-----------+           <-----+   onvif    |
   pub  rep          pub   rep            pub    rep             |     +------------+
    ^    ^            ^     ^              ^      ^              |  
    |    |            |     |              |      |              |  
    |    |            |     |              |      |              | req +------------+  
    +----+------------+-----+--------------+------+--------------+-----+    webs    |  
    |    |            |     |              |      |              |     +------------+  
    |    |            |     |              |      |              |  
    |    |            |     |              |      |              | req +------------+  
    v    v            v     v              v      v              <-----+    rtsps   |  
   pub  rep          pub   rep            pub    rep                   +-------+--+-+  
+------------+    +------------+        +------------+                         |  |  
|    bsp     |    |    codec   |cfifo <-|     rec    |file <-------------------+  |  
+------------+    +------------+  ^     +------------+                            |  
                                  |                                               |  
                                  +-----------------------------------------------+  
  
+-----------------------------------------------------------------------------------+  
|                                linux && HisiSDK                                   |  
+-----------------------------------------------------------------------------------+  
  
```  
  
  
## startup sequence
```  
  BSP  CODEC  SVP   REC   USER1  RTSPS  WEBS ONVIF  APP
   +     +     +     +     +       +     +     +     +  
   |     |     |     |     |       |     |     |     |  
   |     |     |     |     |       |     |     |     |  
+--v-----v-----v-----v-----v-------v-----v-----v-----v----> time;
```
  
## compile:  

```  
source build/3559 && make 
```