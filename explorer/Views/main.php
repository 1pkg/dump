    <span style="float:left;">
        <form action="/" method="get">
            <input type="hidden" name="operation" value="back">
            <button class="arrow-button" <?php if($forwardBack["back"] != true) echo "disabled"?>>
                <?php if ($forwardBack["back"] == true): ?>
                <img src="../Images/back-button-active.png" class="img-rounded" />
                <?php else: ?>
                <img src="../Images/back-button-not-active.png" class="img-rounded" />
                <?php endif; ?>
            </button>
        </form>
    </span>

    <span style="float:left;">
    <form action="/" method="get">
        <input type="hidden" name="operation" value="forward">
        <button class="arrow-button" <?php if($forwardBack["forward"] != true) echo "disabled"?>>
            <?php if ($forwardBack["forward"] == true): ?>
            <img src="../Images/forward-button-active.png" class="img-rounded" />
            <?php else: ?>
            <img src="../Images/forward-button-not-active.png" class="img-rounded" />
            <?php endif; ?>
        </button>
    </form>
    </span>

    <span style="float:left;">
    <form action="/" method="get">
        <input  type="hidden" name="operation" value="set">
        <input type="text" name="name" value=<?='"' . $path . '"'?>>
    </form>
    </span>

    <span style="float:left;">
    <form action="/" method="get">
        <input type="hidden" name="operation" value="search">
        <input type="text" name="name" placeholer="search">
    </form>
    </span>
