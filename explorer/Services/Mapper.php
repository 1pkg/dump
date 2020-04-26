<?php

namespace Services;

class Mapper
{
    public static function map($operation, $query)
    {
        $invoker = \application::getInstance()->getInvoker();

        switch($operation)
        {
            case "set":
                $invoker->set($query->name);
                break;

            case "step":
                $invoker->step($query->name);
                break;

            case "forward":
                $invoker->forward();
                break;

            case "back":
                $invoker->back();
                break;

            case "father":
                $invoker->father();
                break;

            case "root":
                $invoker->root();
                break;

            case "open":
                $invoker->open(
                    $query->name,
                    $query->id
                );
                break;

            case "save":
                $invoker->save(
                    $query->name,
                    $query->data
                );
                break;

            case "create_file":
                $invoker->create_file($query->name);
                break;

            case "create_directory":
                $invoker->create_directory($query->name);
                break;

            case "rename":
                $invoker->rename(
                    $query->from,
                    $query->to
                );
                break;

            case "delete":
                $invoker->delete($query->names);
                break;

            case "move":
                $invoker->move($query->names);
                break;

            case "copy":
                $invoker->copy($query->names);
                break;

            case "paste":
                $invoker->paste();
                break;

            case "find":
                $invoker->find($query->pattern);
                break;

            case "sort":
                $invoker->sort($query->field);
                break;

            case "show":
            case "":
                $invoker->show();
                break;

            default:
                throw new \Exception("operation cannot be recognized");
        }
    }
}

?>