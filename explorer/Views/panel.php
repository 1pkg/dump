<div class="navigation-panel">
    <form action="/" method="get" class="form-element-inline">
        <input type="hidden" name="operation" value="back">
        <button class="arrow-button" id="back" <?php if($back != true) echo "disabled"?>>
            <?php if ($back == true): ?>
            <img src="../Images/back-button-active.png" class="img-rounded" />
            <?php else: ?>
            <img src="../Images/back-button-not-active.png" class="img-rounded" />
            <?php endif; ?>
        </button>
    </form>

    <form action="/" method="get" class="form-element-inline">
        <input type="hidden" name="operation" value="forward">
        <button class="arrow-button" id="forward" <?php if($forward != true) echo "disabled"?>>
            <?php if ($forward == true): ?>
            <img src="../Images/forward-button-active.png" class="img-rounded" />
            <?php else: ?>
            <img src="../Images/forward-button-not-active.png" class="img-rounded" />
            <?php endif; ?>
        </button>
    </form>

    <form action="/" method="get" class="form-element-inline">
        <input type="hidden" name="operation" value="set">
        <input type="text" name="name" value=<?='"' . $path . '"'?> class="text-box" id="path">
    </form>

    <form action="/" method="get" class="form-element-inline">
        <input type="hidden" name="operation" value="find">
        <input type="text" name="pattern" placeholder="Search: use regex here" class="text-box" id="find">
    </form>
</div>