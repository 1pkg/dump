function initialize()
{
    $(".modal-dialog").draggable(
        {
            handle: ".modal-header"
        }
    );
}

function update(arguments)
{
    $.redirect(
        '/',
        arguments,
        "GET"
    );
}

function updateAsync(arguments, callback)
{
    $.ajax({
        url: "/",
        type: "GET",
        data: arguments
    }).done(callback);
}