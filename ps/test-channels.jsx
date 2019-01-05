#target photoshop 

//获得当前所选通道
var channelRef = app.activeDocument.channels.getByName("Alpha 1");

//传入需要改的值
//var red = ; 
//var blue = ;
//var green = ;

//将该通道的RGB颜色的blue值修改为255。
//if (channelRef.name == "蓝")
    channelRef.color.rgb.blue = Math.random() * 255;
i//f (channelRef.name == "红")
    channelRef.color.rgb.red = Math.random() * 255;
//if (channelRef.name == "绿")
channelRef.color.rgb.green = Math.random() * 255;

//通过调用[alert]命令，弹出警告框，显示该图像的直方图信息。
//alert(channelRef.color.rgb.red+"/"+channelRef.color.rgb.green+"/"+channelRef.color.rgb.blue);

  
