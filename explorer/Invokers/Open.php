<?php

namespace Invokers;

class Open implements \Interfaces\Invoker
{
    public function __construct($name, $id)
    {
        $this->_name = $name;
        $this->_id = $id;
    }

    public function invoke()
    {
        $data = \application::getInstance()->getFileSystem()->read(
            $this->_name
        );

        \Flight::render(
            'open.php',
            array(
                "content" => $data,
                "name" => $this->_name,
                "id" => $this->_id
            )
        );
    }

    private $_name;
    private $_id;
}