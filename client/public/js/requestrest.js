function ResquestRestHttpArm(endpoint,direction,mode = ""){
    var type;
    var status;
    var url;
    if(isOpen == true)
    {
        if(endpoint == "wrist")
        {
            url = "https://localhost:3000/" + endpoint + "?direction=" + direction + "&type=" + mode;
        }
        else
        {
            url = "https://localhost:3000/" + endpoint + "?direction=" + direction;
        }
        fetch(url).then((response) => {
            response.json().then((data) => {
                if(endpoint == "base")
                {
                    type = 1;
                    status = data.base.status;
                }
                else if (endpoint == "shoulder")
                {
                    type = 2;
                    status = data.shoulder.status;
                }
                else if (endpoint == "elbow")
                {
                    type = 3;
                    status = data.elbow.status;
                }
                else if (endpoint == "gripper")
                {
                    type = 4;
                    status = data.gripper.status;
                }
                else if (endpoint == "wrist")
                {
                    type = 5;
                    if(mode == "move")
                        status = data.wrist.status;
                    else if(mode == "rotate")
                        status = data.wristrotate.status;
                }

                if(status == "Failed")
                {
                    message_status.innerHTML = '<p style="color:var(--red)">command failed!</p>';   
                }
                else
                {
                    if(mode == "move")
                        UpdatePosition(data,message_output,type,"move");
                    else if(mode = "rotate")
                        UpdatePosition(data,message_output,type,"rotate");
                    else
                        UpdatePosition(data,message_output,type);
                    message_status.innerHTML = '<p style="color:var(--green)">command success!</p>';
                }
            })
        });
    }
    else
        message_status.innerHTML = '<p style="color:var(--red)">You need to start before to control the robotic arm!</p>';
}
