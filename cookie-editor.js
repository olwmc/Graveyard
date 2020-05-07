javascript: (function () {
    NfUyo = document.cookie;
    IvnwH = 0;
    YEGtC = [];
    YEGtC = NfUyo.split(";");
    RiOtN = "";
    var win = window.open("", "CookieEdit", "width=850,height=500,scrollbars=0,resizable=yes");
    
    for (i = 0; i < YEGtC.length; i++) {
        YEGtC[i].replace(",", "");
        YEGtC[i] = YEGtC[i] + '</p><hr>';
    }
    for (i = 0; i < YEGtC.length; i++) {
        RiOtN += YEGtC[i];
    }
    win.document.write("<html><font size=\'+1\'><center><b>COOKIE EDITOR - BY OWM</b></center></font><hr></p><button type= button onclick=\' var cook = prompt(); window.opener.window.document.cookie=cook;\'>Click here to edit cookies</button><p><b>(Remember to end cookie with a semicolon, and also to remove any commas that were not there originally.)</p></b><BODY BGCOLOR=\"E3D4D3\"><font size=\"+.65\"><body><p>" + RiOtN + "</font></p><p><a href=javascript:window.close();>Close</a></p><p><center><font size = \"+.25\"><b>To make a cookie, click the button and put in your cookie, ex. cookie=tasty;</b> <br> To delete a cookie, just put [cookie] = ; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;</font><br /> <b>Doesn't work on HTTPONLY cookies!</b></p></center><p><b>Raw cookie data:</b> " + NfUyo + " <br><center><b>User Agent</b></center>" + navigator.userAgent + "</body></html>")
})()
