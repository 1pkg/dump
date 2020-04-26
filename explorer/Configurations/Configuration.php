<?php

namespace Configurations;

class Configuration
{
    public function __construct()
    {
        if(\Session::read("configurations") === false)
        {
            $configuration = parse_ini_file(
                __DIR__ . "/../configuration.ini",
                true
            );

            $this->ftp($configuration["ftp"]);
            $this->path(
                $configuration["path"],
                $configuration["ftp"]["use"]
            );
            $this->quick_file_system(
                $configuration["quick_file_system"],
                $configuration["ftp"]["use"]
            );
            $this->sort($configuration["sort"]);

            \Session::write(
                "configurations",
                $configuration
            );
        }

        $this->_configurations = \Session::read("configurations");
    }

    private function ftp(&$ftp)
    {
        if(empty($ftp["use"]))
            $ftp["use"] = false;
        else
        {
            if(
                !empty($ftp["host"]) &&
                !empty($ftp["user_name"]) &&
                !empty($ftp["password"])
            )
            {
                $configuration = array(
                    "host" => $ftp["host"],
                    "username" => $ftp["user_name"],
                    "password" => $ftp["password"]
                );
                if(!empty($ftp["port"]))
                    $configuration["port"] = $ftp["port"];
                if(!empty($ftp["time_out"]))
                    $configuration["timeOut"] = $ftp["time_out"];
                if(!empty($ftp["perm_public"]))
                    $configuration["permPublic"] = $ftp["perm_public"];
                $ftp["configuration"] = $configuration;
            }
            else
                $ftp["use"] = false;
        }

        unset($ftp["host"]);
        unset($ftp["user"]);
        unset($ftp["password"]);
        unset($ftp["port"]);
        unset($ftp["time_out"]);
    }

    private function path(&$path, $ftp)
    {
        if(empty($path["root"]))
        {
            if($ftp)
                $path["root"] = "/";
            else
                $path["root"] = __DIR__ . "/..";
        }

        if(empty($path["separator"]))
            $path["separator"] = '/';

        if(\Session::read("current") === false)
            \Session::write(
                "current",
                $path["root"]
            );

        if (\Session::read("paths") === false) {
            $arr = array();
            $arr[] = "";
            \Session::write(
                "paths",
                $arr
            );
        }

        if(\Session::read("index") === false)
            \Session::write("index", 0);
    }

    private function quick_file_system(&$quick_file_system, $ftp)
    {
        if(empty($quick_file_system["use"]))
            $quick_file_system["use"] = false;

        if(
            !empty($quick_file_system["scheme"]) &&
            !empty($quick_file_system["host"]) &&
            !empty($quick_file_system["port"])
        )
        {
            $configuration = array(
                $quick_file_system["scheme"],
                $quick_file_system["host"],
                $quick_file_system["port"]
            );
            $quick_file_system["configuration"] = $configuration;
        }

        if($ftp)
        {
            $quick_file_system["use"] = false;
            unset($quick_file_system["configuration"]);
        }
        unset($quick_file_system["scheme"]);
        unset($quick_file_system["host"]);
        unset($quick_file_system["port"]);
    }

    private function sort(&$sort)
    {
        if(empty($sort["type"]))
            $sort["type"] = "regular";
    }

    public function __get($field)
    {
        return $this->_configurations[$field];
    }

    private $_configurations;
}

?>
