var ns4 = (document.layers);
var ie4 = (document.all && !document.getElementById);
var ie5 = (document.all && document.getElementById);
var ns6 = (!document.all && document.getElementById);

function openInWindow( url ) {
  var newWindow = window.open(url);
  newWindow.focus();
  //newWindow.moveBy(10,0); // causes weird "access is denied" error
}

function loadPg( fn ) {
    if (fn == null) return;
    var url;
    if ( fn.substring(0,6) == "POPUP:" ) {
        url = fn.substring(6);
	openInWindow( url );
	return;
    }
    else if ( fn.substring(0,5) == "LINK:" ) {
        url = fn.substring(5);
    }
    else {
        url = "functions/" + fn + ".html";
    }

    if (!document.getElementById) {
       var fm = top.frames["rightFrame"];
       if (fm != null ) {
         fm.location = url;
       }
    }     
    else {
       var fm = top.document.getElementById('rightFrm');
	if ( fm == null ) {
           fm = parent.parent.document.getElementById('rightFrm');
        }
	if ( fm == null ) {
alert("fm is still null!!");
        }
	else { fm.src = url; }
   }
}