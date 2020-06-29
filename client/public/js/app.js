const command_bleft = document.getElementById("bleft");
const command_bup = document.getElementById("bup");
const command_bright = document.getElementById("bright");
const command_bdown = document.getElementById("bdown");
const command_bl1 = document.getElementById("buttonl1");
const command_bl2 = document.getElementById("buttonl2");
const command_br1 = document.getElementById("buttonr1");
const command_br2 = document.getElementById("buttonr2");
const command_bnorth = document.getElementById("buttonnorth");
const command_bsouth = document.getElementById("buttonsouth");
const command_beast = document.getElementById("buttoneast");
const command_bwest = document.getElementById("buttonwest");
const message_output      = document.querySelector('#output');
const message_status    = document.querySelector('#outputfailed');
const start_stop_button = document.getElementById("start/stop");

var isOpen = false; 
var ipAddr = "https://127.0.0.1:3000";
command_bleft.onclick = function(){
    ResquestRestHttpArm("base",0);
}

command_bup.onclick = function(){
    ResquestRestHttpArm("shoulder",1);
}

command_bright.onclick = function(){
    ResquestRestHttpArm("base",1);
}

command_bdown.onclick = function(){
    ResquestRestHttpArm("shoulder",0);
}

command_bl1.onclick = function(){
    ResquestRestHttpArm("gripper",1);
}

command_bl2.onclick = function(){
    ResquestRestHttpArm("wrist",0,"rotate");
}

command_br1.onclick = function(){
    ResquestRestHttpArm("gripper",0);
}

command_br2.onclick = function(){
    ResquestRestHttpArm("wrist",1,"rotate");
}

command_bnorth.onclick = function(){
    ResquestRestHttpArm("elbow",0);
}

command_bsouth.onclick = function(){
    ResquestRestHttpArm("elbow",1);
}

command_beast.onclick = function(){
    ResquestRestHttpArm("wrist",1,"move");
}

command_bwest.onclick = function(){
    ResquestRestHttpArm("wrist",0,"move");
}

start_stop_button.onclick = function(event){
    if(start_stop_button.textContent == "start")
    {
        const url = ipAddr + "/open";
        fetch(url).then((response) => {
            response.json().then((data) => {
                if(data.open.status == "OK"){
                    UpdatePosition(data.open,message_output,0);
                    message_status.innerHTML = '<p style="color:var(--green)">command success!</p>';
                    isOpen = true;
                }
                else
                {
                    message_status.innerHTML = '<p style="color:var(--red)">command failed!</p>';
                }
            })
        })
        start_stop_button.textContent = "stop";
    }
    else
    {
        const url = ipAddr + "/close";
        fetch(url).then((response) => {
            response.json().then((data) => {
                if(data.close.status == "OK"){
                    message_status.innerHTML = '<p style="color:var(--green)">command success!</p>';
                    isOpen = false;
                }
                else
                {
                    message_status.innerHTML = '<p style="color:var(--red)">command failed!</p>';
                }
            })
        })
        start_stop_button.textContent = "start";
    }
}

