<?php

require_once dirname(__FILE__) . '/../bitcoin.inc';

/**
 * Test class for Bitcoin.
 *
 * Copyright (C) 2010 by Mike Gogulski - All rights reversed http://www.unlicense.org/ (public domain)
 *
 * @author Mike Gogulski - http://www.nostate.com/ http://www.gogulski.com/
 */
class BitcoinTest extends PHPUnit_Framework_TestCase {
	protected function setUp() {
	}

	protected function tearDown() {
	}

  /**
   * @todo Implement testHash160ToAddress().
   */
  public function testHash160ToAddress() {
    // Remove the following lines when you implement this test.
    $this->markTestIncomplete('This test has not been implemented yet.');
  }

  /**
   * @todo Implement testAddressToHash160().
   */
  public function testAddressToHash160() {
    // Remove the following lines when you implement this test.
    $this->markTestIncomplete('This test has not been implemented yet.');
  }

  /**
   * Test Bitcoin::checkAddress() with various good and bad addresses.
   */
  public function testCheckAddress() {
  	$this->assertTrue(TRUE);
    $this->assertTrue(Bitcoin::checkAddress("1pA14Ga5dtzA1fbeFRS74Ri32dQjkdKe5"));
    $this->assertTrue(Bitcoin::checkAddress("1MU97wyf7msCVdaapneW2dW1uXP7oEQsFA"));
    $this->assertTrue(Bitcoin::checkAddress("1F417eczAAbh41V4oLGNf3DqXLY72hsM73"));
    $this->assertTrue(Bitcoin::checkAddress("1ASgNrpNNejRJVfqK2jHmfJ3ZQnMSUJkwJ"));
    $this->assertFalse(Bitcoin::checkAddress("1ASgNrpNNejRJVfqK2jHmfJ3ZQnMSUJ"));
    $this->assertFalse(Bitcoin::checkAddress("1111111fnord"));
  }

  /**
   * @todo Implement testPubKeyToAddress().
   */
  public function testPubKeyToAddress() {
    // Remove the following lines when you implement this test.
    $this->markTestIncomplete('This test has not been implemented yet.');
  }

  /**
   * Test the Bitcoin::remove0x() function.
   */
  public function testRemove0x() {
  	$this->assertEquals(Bitcoin::remove0x("abcdefg"), "abcdefg");
  	$this->assertEquals(Bitcoin::remove0x("0xabcdefg"), "abcdefg");
  	$this->assertEquals(Bitcoin::remove0x("0Xabcdefg"), "abcdefg");
  }
}
?>
