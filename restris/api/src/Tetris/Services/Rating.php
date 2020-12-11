<?php

namespace Tetris\Services;

class Rating
{
    const ZSET_KEY = 'rating-zset-key';
    const ZSET_LIMIT = 5;

    public function __construct(\Predis\Client $redis)
    {
        $this->__redis = $redis;
    }

    public function top(): array
    {
        return $this->__redis->zrevrange(self::ZSET_KEY, 0, self::ZSET_LIMIT, 'WITHSCORES');
    }

    public function push(string $name, int $score): void
    {
        $zscore = $this->__redis->zscore(self::ZSET_KEY, $name);
        if (!is_null($zscore) && $zscore >= $score) {
            return;
        }

        $this->__redis->zrem(self::ZSET_KEY, $name);
        $this->__redis->zadd(self::ZSET_KEY, $score, $name);
        if (($count = $this->__redis->zcount($name, '-inf', '+inf')) > self::ZSET_LIMIT) {
            $this->__redis->zremrangebyrank($name, 0, $count - self::ZSET_LIMIT);
        }
    }

    private $__redis;
}
