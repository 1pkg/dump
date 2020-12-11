<?php

namespace Tetris\Model\Interfaces;

interface IObject
{
    public function type(): string;

    public function data(): array;

    public function traverse(callable $callback): void;

    public function format(): array;
}
