<?php

namespace Tetris\Services\Tests;

use Tetris\Model\Objects;
use Tetris\Services;
use PHPUnit\Framework\TestCase;

class UtilitiesTest extends TestCase
{
    const FIGURES_ENUM = [
        Objects\Figure::TYPE_CRANE,
        Objects\Figure::TYPE_LINE,
        Objects\Figure::TYPE_FIRST_L,
        Objects\Figure::TYPE_SECOND_L,
        Objects\Figure::TYPE_FIRST_Z,
        Objects\Figure::TYPE_SECOND_Z,
        Objects\Figure::TYPE_SQUARE,
    ];

    const START_COORD_X = 0;
    const START_COORD_Y = 5;

    protected $redisMock;

    public function setUp()
    {
        $factory = new \M6Web\Component\RedisMock\RedisMockFactory();
        $this->redisMock = $factory->getAdapter('Predis\Client', true);
    }

    public function testBacthService()
    {
        $batch = new Services\Batch();
        $figures = $batch->make();

        $this->assertEquals(count($figures), Services\Batch::BATCH_LENGTH);
        foreach ($figures as $figure) {
            $this->assertTrue(in_array($figure, self::FIGURES_ENUM, true));
        }
    }

    public function testBacthShiftService()
    {
        $batch = new Services\Batch();
        $figures = $batch->make();
        $batch->shift($figures);
        $batch->shift($figures);
        $batch->shift($figures);
        $batch->shift($figures);

        $this->assertEquals(count($figures), Services\Batch::BATCH_LENGTH);
        foreach ($figures as $figure) {
            $this->assertTrue(in_array($figure, self::FIGURES_ENUM, true));
        }
    }

    /**
     * @expectedException \Exception
     */
    public function testFabricExceptionService()
    {
        $fabric = new Services\Fabric();
        $fabric->create([]);
    }

    public function testFabricService()
    {
        $fill = array_fill(0, Objects\Deck::SIZE_HEIGHT, array_fill(0, Objects\Deck::SIZE_WIDTH, 1));
        $fabric = new Services\Fabric();
        $deck = $fabric->create(['type' => Objects\Deck::TYPE_DECK, 'deck' => $fill]);
        $line = $fabric->create(['type' => Objects\Figure::TYPE_LINE, 'coordX' => self::START_COORD_X, 'coordY' => self::START_COORD_Y, 'rotation' => Objects\Figure::ROTATION_0], $deck);
        $square = $fabric->create(['type' => Objects\Figure::TYPE_SQUARE, 'coordX' => self::START_COORD_X, 'coordY' => self::START_COORD_Y, 'rotation' => Objects\Figure::ROTATION_0], $deck);

        $this->assertInstanceOf(Objects\Deck::class, $deck);
        $this->assertEquals($deck->data()['deck'], $fill);
        $this->assertInstanceOf(Objects\Figures\Line::class, $line);
        $this->assertInstanceOf(Objects\Figures\Square::class, $square);
    }

    public function testStorageService()
    {
        $storage = new Services\Storage($this->redisMock);
        $storage->set('key', ['order' => 1, 'data' => [1, 2, 3]]);
        // $storage->set('del-key', []); #m6web/redis-mock count(str) issue
        // $storage->remove('del-key'); #m6web/redis-mock count(str) issue

        // $this->assertFalse($storage->has('del-key')); #m6web/redis-mock count(str) issue
        $this->assertFalse($storage->has('non-key'));
        $this->assertTrue($storage->has('key'));
        $this->assertEquals($storage->get('key'), ['order' => 1, 'data' => [1, 2, 3]]);
    }

    public function testRatingService()
    {
        $this->markTestSkipped('m6web/redis-mock not support needle operations pool');

        $supposeRating = [
            'jack' => 800,
            'ryan' => 500,
            'david' => 400,
            'jack' => 300,
            'bob' => 200,
        ];
        $rating = new Services\Rating($this->redisMock);
        $rating->push('bob', 200);
        $rating->push('jack', 300);
        $rating->push('john', 100);
        $rating->push('jack', 800);
        $rating->push('ryan', 500);
        $rating->push('david', 400);
        $top = $rating->top();

        $this->assertEquals(count($top), Services\Rating\ZSET_LIMIT);
        $this->assertEquals($top, $supposeRating);
    }
}
