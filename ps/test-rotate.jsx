#target photoshop 

// Save selected layer to variable:  
    var originalStem = app.activeDocument.activeLayer;  
  //输入角度
    var angle = prompt ("Processing \""+originalStem.name+"\"\n旋转多少角度? (From 0 to 360)", 30); 
  //旋转角度
    originalStem.rotate(angle, AnchorPosition.MIDDLECENTER);  
  
