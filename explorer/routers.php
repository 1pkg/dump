<?php

Flight::route(
    '/',
    function()
    {
        $request = Flight::request();
        $operation = $request->query->operation === null
            ? ""
            : $request->query->operation;
        \Services\Service::map(
            $operation,
            $request->query
        );
    }
);

Flight::map(
    'error',
    function(Exception $ex)
    {
        echo "<pre>Something bad happened:\n    " . $ex->getMessage() . "<br>" . $ex->getTraceAsString() . "</pre>";
    }
);

Flight::map(
    'notFound',
    function()
    {
        echo '<img src="/Images/404.png" />';
    }
);

?>
