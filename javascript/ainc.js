var count = 0;
var incMatrix = new Array();
function change(id){
	var box = document.getElementById("box" + id);
	if(count == 0 && incMatrix[id - 1] != 1){
		box.style.backgroundPosition = "-400px 0px";
		incMatrix[id - 1] = 1;
		count = 1;
	}else if(incMatrix[id - 1] != 1){
		box.style.backgroundPosition = "0px 0px";
		incMatrix[id - 1] = 1;
		count = 0;
	}

}