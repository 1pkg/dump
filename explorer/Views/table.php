<table class = "table table-hover table-condensed table-bordered">
    <thead>
        <tr>
            <td>
                <a  class="btn" href=<?="/?operation=sort&field=name"?>>
                    Name
                </a>
            </td>
            <td>
                <a class="btn" href=<?="/?operation=sort&field=mimetype"?>>
                    Type
                </a>
            </td>
            <td>
                <a class="btn" href=<?="/?operation=sort&field=timestamp"?>>
                    TimeStamp
                </a>
            </td>
            <td>
                <a class="btn" href=<?="/?operation=sort&field=size"?>>
                    Size
                </a>
            </td>
        <tr>
    </thead>
    <tbody>
        <?php foreach($infos as $info): ?>
        <tr class="entry-info">
            <td class="info-name">
                <?php if ($info["mimetype"] == "directory"): ?>
                <img src="../Images/directory.png" />
                <?php else: ?>
                <img src="../Images/file.png" />
                <?php endif; ?>
                <span><?=$info["name"]?></span>
            </td>
            <td class="info-mimetype"><?=$info["mimetype"]?></td>
            <td class="info-timestamp"><?=date("Y.m.d H:i", $info["timestamp"])?></td>
            <td class="info-size"><?=!empty($info["size"]) ? $info["size"] . " byte" : "";?></td>
        </tr>
        <?php endforeach; ?>
    </tbody>
</table>
