<?php

namespace Invokers;

class Show implements \Interfaces\Invoker
{
    public function __construct($infos = null)
    {
        $this->_infos = $infos;
    }

    public function invoke()
    {
        $fileSystem = \application::getInstance()->getFileSystem();
        $this->_infos = empty($this->_infos)
            ? $fileSystem->getInfos()
            : $this->_infos;

        $currentPath = \application::getInstance()->getCurrentPath();
        \Flight::render(
            "panel",
            array(
                "forward" => $currentPath->canForward(),
                "back" => $currentPath->canBack(),
                "path" => $currentPath->getRelative()
            ),
            "panel"
        );

        \Flight::render(
            "table",
            array(
                "infos" => $this->_infos
            ),
            "table"
        );

        \Flight::render(
            "menu",
            array(
            ),
            "menu"
        );

        \Flight::render(
            "layout"
        );
    }

    private $_infos;
}
