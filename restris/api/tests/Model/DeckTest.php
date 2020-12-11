<?php

namespace Tetris\Model\Tests;

use Tetris\Model\Objects;
use Tetris\Model\Objects\Figures;
use PHPUnit\Framework\TestCase;

class DeckTest extends TestCase
{
    const START_COORD_X = 0;
    const START_COORD_Y = 5;

    public function testAutoFillDeck()
    {
        $fill = array_fill(0, Objects\Deck::SIZE_HEIGHT, array_fill(0, Objects\Deck::SIZE_WIDTH, 0));
        $deck = new Objects\Deck([]);

        $this->assertEquals($deck->data()['deck'], $fill);
    }

    public function testManualFillDeck()
    {
        $fill = array_fill(0, Objects\Deck::SIZE_HEIGHT, array_fill(0, Objects\Deck::SIZE_WIDTH, 1));
        $deck = new Objects\Deck($fill);

        $this->assertEquals($deck->data()['deck'], $fill);
    }

    public function testClearDeck()
    {
        $fill = [
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            [1, 1, 1, 1, 1, 0, 0, 0, 0, 0],
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
        ];
        $fillResult = [
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            [1, 1, 1, 1, 1, 0, 0, 0, 0, 0],
        ];
        $deck = new Objects\Deck($fill);
        $result = $deck->clear();

        $this->assertEquals($result, 7);
        $this->assertEquals($deck->data()['deck'], $fillResult);
    }

    public function testIntersectDeck()
    {
        $fill = [
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            [1, 1, 0, 0, 0, 0, 1, 1, 1, 1],
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
        ];
        $deck = new Objects\Deck($fill);
        $line = new Figures\Line($deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_90);
        $line->update();
        $line->update();
        $result = $deck->intersect($line);

        $this->assertTrue($result);
    }

    public function testNonIntersectDeck()
    {
        $fill = [
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            [1, 1, 0, 0, 0, 0, 1, 1, 1, 1],
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
        ];
        $deck = new Objects\Deck($fill);
        $line = new Figures\Line($deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_90);
        $line->update();
        $result = $deck->intersect($line);

        $this->assertFalse($result);
    }

    public function testMergeDeck()
    {
        $fill = [
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            [1, 1, 0, 0, 0, 0, 1, 1, 1, 1],
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
        ];
        $fillResult = [
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
        ];
        $deck = new Objects\Deck($fill);
        $line = new Figures\Line($deck, self::START_COORD_X, self::START_COORD_Y, Objects\Figure::ROTATION_90);
        $line->update();
        $line->update();
        $deck->merge($line);

        $this->assertEquals($deck->data()['deck'], $fillResult);
    }

    public function testOverDeck()
    {
        $fill = [
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            [1, 1, 1, 1, 1, 0, 0, 0, 0, 0],
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
        ];
        $deck = new Objects\Deck($fill);
        $result = $deck->over();

        $this->assertTrue($result);
    }

    public function testNonOverDeck()
    {
        $fill = [
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
        ];
        $deck = new Objects\Deck($fill);
        $result = $deck->over();

        $this->assertFalse($result);
    }

    public function testFormatDeck()
    {
        $fill = [
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 0),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
            array_fill(0, Objects\Deck::SIZE_WIDTH, 1),
        ];
        $fillResult = array_fill(0, Objects\Deck::SIZE_HEIGHT - Objects\Deck::SIZE_HEIGHT_INTERNAL, array_fill(0, Objects\Deck::SIZE_WIDTH, 1));
        $deck = new Objects\Deck($fill);
        $result = $deck->format();

        $this->assertEquals($result, $fillResult);
    }
}
