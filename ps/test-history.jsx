#target photoshop 

var  doc = app.activeDocument;

//获取倒数第二步历史记录数；

var i=0;
while (doc.activeHistoryState != doc.historyStates[i] )
    i=i+1;

//将历史记录数状态设置成倒数第二步，也就是回退了一步;

doc.activeHistoryState = doc.historyStates[i-1];


  
