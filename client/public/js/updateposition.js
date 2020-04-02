function UpdatePosition(data, message_output, type, mode = "")
{
    if(type == 0) {
        UpdatePosition.base = data.base;
        UpdatePosition.shoulder = data.shoulder;
        UpdatePosition.elbow = data.elbow;
        UpdatePosition.gripper = data.gripper;
        UpdatePosition.wrist   = data.wrist;
        UpdatePosition.wristrotation = data.wristrotation;
    }

    if(type == 1){
        UpdatePosition.base = data.base.positionCurrent;
    }
    else if(type == 2){
        UpdatePosition.shoulder = data.shoulder.positionCurrent;
    }
    else if(type == 3){
        UpdatePosition.elbow = data.elbow.positionCurrent;
    }
    else if(type == 4){
        UpdatePosition.gripper = data.gripper.positionCurrent;
    }
    else if(type == 5){
        if(mode == "move")
            UpdatePosition.wrist = data.wrist.positionCurrent;
        else if (mode == "rotate")
            UpdatePosition.wristrotation = data.wristrotation.positionCurrent;
    }

    message_output.innerHTML = '<h3>Position:</h1>base: ' +  UpdatePosition.base + '<br><br>shoulder: ' + UpdatePosition.shoulder
                                + '<br><br>elbow: ' + UpdatePosition.elbow + '<br><br>gripper: ' + UpdatePosition.gripper
                                + '<br><br>wrist: ' + UpdatePosition.wrist + '<br><br>wrist rotation: ' + UpdatePosition.wristrotation;
}
