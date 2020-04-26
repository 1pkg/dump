var clicked = null;
function showMenu(event)
{
    clicked = null;
    event.preventDefault();

    var element = document.elementFromPoint(event.pageX, event.pageY);
    var parent = $(element).parent();
    if(parent.is("tr") && parent.attr("class") == "entry-info")
    {
        var type = parent.children(".info-mimetype").html();
        clicked = parent.children(".info-name").children("span").html();
        if(type == "directory")
        {
            show(
                "#menu-directory",
                event.pageX,
                event.pageY
            );

            clicked == ".."
                ? disable()
                : enable();
        }
        else
            show(
                "#menu-file",
                event.pageX,
                event.pageY
            );
    }
    else
        show(
            "#menu-empty",
            event.pageX,
            event.pageY
        );
}

function hideMenu(event)
{
    var id = $(event.target).parent().attr("id");

    if(id != "menu-directory")
        hide("#menu-directory");

    if(id != "menu-file")
        hide("#menu-file");

    if(id != "menu-empty")
        hide("#menu-empty");
}

function disable()
{
    $("#menu-directory").find("[data-operation='delete']").hide();
    $("#menu-directory").find("[data-operation='rename']").hide();
    $("#menu-directory").find("[data-operation='move']").hide();
    $("#menu-directory").find("[data-operation='copy']").hide();
}

function enable()
{
    $("#menu-directory").find("[data-operation='delete']").show();
    $("#menu-directory").find("[data-operation='rename']").show();
    $("#menu-directory").find("[data-operation='move']").show();
    $("#menu-directory").find("[data-operation='copy']").show();
}

function show(id, x, y)
{
    $(id).finish().toggle(100).
        css(
        {
            left: x + "px",
            top: y + "px"
        }
    );
}

function hide(id)
{
    $(id).hide(100);
}

function processFileMenu()
{
    var operation = $(this).attr("data-operation");
    switch(operation)
    {
        case "open":
            openFile(clicked);
            break;

        case "delete":
        case "move":
        case "copy":
            update(
                {
                    operation: operation,
                    names: clicked
                }
            );
            break;

        case "rename":
            bootbox.prompt(
                {
                    message: "Enter entry name",
                    title: "rename",
                    size: "large",
                    callback: function(name)
                    {
                        if(name != null && name != "")
                            update(
                                {
                                    operation: operation,
                                    from: clicked,
                                    to: name
                                }
                            );
                    }
                }
            );
            break;

    }

    hide("#menu-file");
}

function processDirectoryMenu()
{
    var operation = $(this).attr("data-operation");
    switch(operation)
    {
        case "step":
            openDirectory(clicked);
            break;

        case "delete":
        case "move":
        case "copy":
            update(
                {
                    operation: operation,
                    names: clicked
                }
            );
            break;

        case "rename":
            bootbox.prompt(
                {
                    message: "Enter entry name",
                    title: "rename",
                    size: "large",
                    callback: function(name)
                    {
                        if(name != null && name != "")
                            update(
                                {
                                    operation: operation,
                                    from: clicked,
                                    to: name
                                }
                        );
                    }
                }
            );
            break;
    }

    hide("#menu-directory");
}

function processEmptyMenu()
{
    var operation = $(this).attr("data-operation");
    switch(operation)
    {
        case "create_file":
        case "create_directory":
            bootbox.prompt(
                {
                    message: "Enter entry name",
                    title: "create",
                    size: "large",
                    callback: function(name)
                    {
                        if(name != null && name != "")
                            update(
                                {
                                    operation: operation,
                                    name: name
                                }
                            );
                    }
                }
            );
            break;

        case "paste":
            update(
                {
                    operation: operation
                }
            );
            break;
    }

    hide("#menu-empty");
}
