<?php

require_once "ThirdParty/session.php";
require_once "ThirdParty/flight/flight/Flight.php";
require  "ThirdParty/predis/autoload.php";

\Predis\Autoloader::register();

spl_autoload_register(
    function($class)
    {
        $prefix = 'League\\Flysystem\\';
        if (!substr($class, 0, strlen($prefix)) === $prefix)
            return;

        $class = substr($class, strlen($prefix));
        $location = __DIR__ . '/ThirdParty/flysystem/src/' . str_replace('\\', '/', $class) . '.php';

        if (is_file($location))
            require_once($location);
    }
);

spl_autoload_register(
    function($class)
    {
        $relative = str_replace("\\", "/", $class);
        $file = __DIR__ . '/' . $relative . '.php';

        if (!is_file($file))
            return;

        require_once($file);
    }
);

?>