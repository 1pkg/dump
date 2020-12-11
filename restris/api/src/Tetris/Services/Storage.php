<?php

namespace Tetris\Services;

class Storage
{
    public function __construct(\Predis\Client $redis)
    {
        $this->__redis = $redis;
    }

    public function has(string $key): bool
    {
        return $this->__redis->exists($key);
    }

    public function set(string $key, array $data): void
    {
        $this->__redis->set($key, serialize($data));
        $this->__redis->expire($key, 1800);
    }

    public function get(string $key): array
    {
        return unserialize($this->__redis->get($key));
    }

    public function remove(string $id): void
    {
        $this->__redis->del($id);
    }

    private $__redis;
}
