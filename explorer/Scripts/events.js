$(function()
{
    $(document).ajaxComplete(initialize);

    $("tr").dblclick(open);

    $(document).bind(
        "contextmenu",
        showMenu
    );

    $(document).bind(
        "mousedown",
        hideMenu
    );

    $("#menu-file li").click(processFileMenu);

    $("#menu-directory li").click(processDirectoryMenu);

    $("#menu-empty li").click(processEmptyMenu);
});