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


// URL Encoded
javascript:(function%20()%20%7B%20NfUyo%20%3D%20document.cookie%3B%20IvnwH%20%3D%200%3B%20YEGtC%20%3D%20%5B%5D%3B%20YEGtC%20%3D%20NfUyo.split(%22%3B%22)%3B%20RiOtN%20%3D%20%22%22%3B%20for%20(i%20%3D%200%3B%20i%20%3C%20YEGtC.length%3B%20i%2B%2B)%20%7B%20YEGtC%5BIvnwH%5D.replace(%22%2C%22%2C%20%22%22)%3B%20YEGtC%5BIvnwH%5D%20%3D%20YEGtC%5BIvnwH%5D%20%2B%20%27%3C%2Fp%3E%3Chr%3E%27%3B%20IvnwH%2B%2B%20%7D%20console.log(YEGtC)%3B%20var%20win%20%3D%20window.open(%22%22%2C%20%22CookieEdit%22%2C%20%22width%3D850%2Cheight%3D500%2Cscrollbars%3D0%2Cresizable%3Dno%22)%3B%20for%20(i%20%3D%200%3B%20i%20%3C%20YEGtC.length%3B%20i%2B%2B)%20%7B%20RiOtN%2B%3DYEGtC%5Bi%5D%3B%20%7D%20function%20remLink()%20%7B%20if%20(window.sList%20%26%26%20window.sList.open%20%26%26%20!window.sList.closed)%20window.sList.opener%20%3D%20null%3B%20%7D%20remLink()%3B%20win.document.write(%22%3Chtml%3E%3Cfont%20size%3D%5C%27%2B1%5C%27%3E%3Ccenter%3E%3Cb%3ECOOKIE%20EDITOR%20-%20BY%20OWM%3C%2Fb%3E%3C%2Fcenter%3E%3C%2Ffont%3E%3Chr%3E%3C%2Fp%3E%3Cbutton%20type%3D%20button%20onclick%3D%5C%27%20var%20cook%20%3D%20prompt()%3B%20window.opener.window.document.cookie%3Dcook%3B%5C%27%3EClick%20here%20to%20edit%20cookies%3C%2Fbutton%3E%3Cp%3E%3Cb%3E(Remember%20to%20end%20cookie%20with%20a%20semicolon.)%3C%2Fp%3E%3C%2Fb%3E%3CBODY%20BGCOLOR%3D%5C%22E3D4D3%5C%22%3E%3Cfont%20size%3D%5C%22%2B.65%5C%22%3E%3Cbody%3E%3Cp%3E%22%20%2B%20RiOtN%20%2B%20%22%3C%2Ffont%3E%3C%2Fp%3E%3Cp%3E%3Ca%20href%3Djavascript%3Awindow.close()%3B%3EClose%3C%2Fa%3E%3C%2Fp%3E%3Cp%3E%3Ccenter%3E%3Cfont%20size%20%3D%20%5C%22%2B.25%5C%22%3E%3Cb%3ETo%20make%20a%20cookie%2C%20click%20the%20button%20and%20put%20in%20your%20cookie%2C%20ex.%20cookie%3Dtasty%3B%3C%2Fb%3E%20%3Cbr%3E%20To%20delete%20a%20cookie%2C%20just%20put%20%5Bcookie%5D%20%3D%20%3B%20expires%3DThu%2C%2001%20Jan%201970%2000%3A00%3A00%20UTC%3B%20path%3D%2F%3B%3C%2Ffont%3E%3Cbr%20%2F%3E%20%3Cb%3EDoesn%27t%20work%20on%20HTTPONLY%20cookies!%3C%2Fb%3E%3C%2Fp%3E%3C%2Fcenter%3E%3Cp%3E%3Cb%3ERaw%20cookie%20data%3A%3C%2Fb%3E%20%22%20%2B%20NfUyo%20%2B%20%22%20%3Cbr%3E%3Ccenter%3E%3Cb%3EUser%20Agent%3C%2Fb%3E%3C%2Fcenter%3E%22%20%2B%20navigator.userAgent%20%2B%20%22%3C%2Fbody%3E%3C%2Fhtml%3E%22)%20%7D)()
