function open()
{
    var type = $(this).children(".info-mimetype").html();
    var name = $(this).children(".info-name").children("span").html();

    if(type == "directory")
        openDirectory(name);
    else
        openFile(name);
}

function openFile(name)
{
    function save()
    {
        bootbox.confirm(
            {
                message: "Save changes to " + name + " ?",
                title: "save",
                size: "large",
                callback: function(result)
                {
                    if(!result)
                        return;

                    var content =
                        $("#" + id).find(".modal-dialog").find(".modal-content").find(".modal-body").find(".content").val();

                    $("#" + id).remove();

                    update(
                        {
                            operation: "save",
                            name: name,
                            data: content
                        }
                    );
                }
            }
        );
    }

    var id = 'id' + (new Date()).getTime();
    updateAsync(
        {
            operation : "open",
            name : name,
            id : id
        },
        function(content)
        {
            $(document.body).append(content);
            $("#" + id).modal(
                {
                    show: true
                }
            );

            $("#" + id).on(
                'hidden.bs.modal',
                save
            );
        }
    )
}

function openDirectory(name)
{
    if(name == "..")
        update(
            {
                operation: "father"
            }
        );
    else
        update(
            {
                operation: "step",
                name: name
            }
        );
}