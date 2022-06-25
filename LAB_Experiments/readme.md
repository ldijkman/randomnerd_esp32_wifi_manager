## Brainstorm subjects

## drag drop HTML elements even touch on phone 
## next is nice
## http://sortablejs.github.io/Sortable/#grid
## maybe nice for ordering div iframes

Platformio visual studio
- https://m1cr0lab-esp32.github.io/remote-control-with-websocket/platformio-ide/
- - x
- - trying platformio https://github.com/ldijkman/Electra_ESP32 


---

With a little HTML knowledge or Guts, you can change the looks of Electra's Switch webpages
- Easy, each device has its own web/cloud editor

---



https://www.youtube.com/shorts/rXHRWjgCcls
---

![2022-06-19-151725_1920x1080_scrot](https://user-images.githubusercontent.com/45427770/174482999-ad6c4155-c257-4a1a-8ee5-c9b1d8df7b5b.png)

garage.local/button.html 
- shows automatic mdns scan 
- - iframed other swithes in the local network 
- - for view control 
- - and text link to the switchpages
- future will be on main page of each switch page automatic mdnsscan to show,control,link other swithes in network in an iframe
- - all html / script so end user can play with it with ace js cloud editor (not like an app with no edit)

https://www.youtube.com/shorts/rXHRWjgCcls

![2022-06-19-083050_1920x1080_scrot](https://user-images.githubusercontent.com/45427770/174468844-1980ec65-92b2-4e38-9028-4abc4ca9b102.png)


-----
-----
-----










## Imagene imageButton 
- => http:// mdns_name or IP /button.html     (processor %???% code for/and button.html added to the ESP32 Version)

https://youtube.com/shorts/WvGHbuReKzs?feature=share

https://youtube.com/shorts/alNpCHc8wV4?feature=share

https://youtube.com/shorts/IJEgNqhAxaU?feature=share

# button.html
https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/LAB_Experiments/button.html

```
<!-- HTML Javascript button.html -->
<!-- each wifi relais switch has a button.html -->
<!-- for showing wifi relais status and control it by image button -->

<!-- u can load it in an iframe on other webpage in the local netwok like used in framed.html -->

<!-- %MDNSNAME% is processed on webserver upload ad filled in with a variable -->
<!-- always use the %percent sign in pairs, like i have to put another not to break the processor / html code % -->
<!-- thats tricky when % is used in style or other elements % -->
```

![2022-06-25-043356_1920x1080_scrot](https://user-images.githubusercontent.com/45427770/175755061-8548368c-9d7e-4f13-9516-50c0f48be436.png)

---


### SO HANDY, the ACE js web cloud editor, 
### for editing the html webserver HTML files on the ESP devices

# IFRAME code to use on other pages
- change the src="http:// ??? /button.html" url link to yours / for android better use IP number links
- - https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/LAB_Experiments/button.html
- 
```

<iframe id="inlineFrameExample"
    title="Inline Frame Example"
    width="120"
    height="150"
    src="http://garage.local/button.html"
    style="border:none; -ms-transform: scale(0.5, 0.5); transform: scale(0.5, 0.5)">
</iframe>


```
could place a bulb on each auto scanned discovered mdns url / each switch device in local network

view and control other switches


## Google Please make mDNS work on Android?
- looks like Google obays to Electra's pleas ;-)
- https://www.androidpolice.com/android-mdns-local-hostname/

use ip numbers button html links for adroid?

# framed.html
https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/LAB_Experiments/framed.html

```
 <!-- HTML Javascript listens for a json wesocket ip's and url name -->
 <!-- and shows a iframe of a remote image button.html -->
 <!-- for showing other wifi relais status and control it  -->

 <!-- %MDNSNAME% is processed on webserver upload ad filled in with a variable -->
 <!-- always use the %percent sign in pairs, like i have to put another not to break the processor / html code % -->
 <!-- thats tricky when % is used in style or other elements % -->
```

![2022-06-25-043928_1920x1080_scrot](https://user-images.githubusercontent.com/45427770/175755165-e94fc976-60f5-47b8-81c9-27dbadb69004.png)

![2022-06-25-044038_1920x1080_scrot](https://user-images.githubusercontent.com/45427770/175755209-c7d0e8be-5806-4181-b6da-373441c6f31b.png)

