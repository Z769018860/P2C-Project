#target photoshop 

// Save selected layer to variable:  
var originalStem = app.activeDocument.activeLayer;  
  
// Ask user for input by showing prompt box and save inputted value to variable:  
var stemsAmount = prompt ("Processing \""+originalStem.name+"\"\nHow many stems do you need? (From 2 to 100)", 12);  
  
// Check that user entered a valid number and, if invalid, show error message and ask for input again  
while(isNaN(stemsAmount) || stemsAmount <= 0 || stemsAmount > 100){  
    // If user clicks "Cancel" button, then exit loop  
    if(stemsAmount == null) break;  
  
    // Show error message…  
    alert("Please enter number in range from 2 to 100");  
    // …and ask for input again  
    stemsAmount = prompt("Processing \""+originalStem.name+"\"\nHow many stems do you need? (From 2 to 100)", 12);  
};  
  
// Run the copying process  
if(stemsAmount != null){   
    // Calculate the rotation angle  
    var angle = 360 / parseInt(stemsAmount);  
  
    // Create a group for stems  
    var stemsGroup = app.activeDocument.layerSets.add();  
        stemsGroup.name = originalStem.name + " ("+stemsAmount+" stems)";  
    // Place original layer in group  
    originalStem.move(stemsGroup, ElementPlacement.INSIDE);  
  
    // Duplicate and rotate layers:  
    for(var i = 1; i < stemsAmount; i++){  
        // Duplicate original layer and save it to the variable  
        var newStem = originalStem.duplicate();  
  
        // Rotate new layer  
        newStem.rotate(angle * i, AnchorPosition.BOTTOMCENTER);  
  
        // Add index to new layers  
        newStem.name = originalStem.name + " " + (i+1);  
  
        // Place new layer inside stems group  
        newStem.move(stemsGroup, ElementPlacement.PLACEATEND);  
    };  
  
    // Add index to the original layer  
    originalStem.name += " 1";  
};  
