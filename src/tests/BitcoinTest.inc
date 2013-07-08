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
    # examples from https://en.bitcoin.it/wiki/Technical_background_of_version_1_Bitcoin_addresses
    $this->assertEquals(Bitcoin::pubKeyToAddress('0450863AD64A87AE8A2FE83C1AF1A8403CB53F53E486D8511DAD8A04887E5B23522CD470243453A299FA9E77237716103ABC11A1DF38855ED6F2EE187E9C582BA6'), '16UwLL9Risc3QfPqBUvKofHmBQ7wMtjvM');
  }

  /**
   * Test the Bitcoin::remove0x() function.
   */
  public function testRemove0x() {
  	$this->assertEquals(Bitcoin::remove0x("abcdefg"), "abcdefg");
  	$this->assertEquals(Bitcoin::remove0x("0xabcdefg"), "abcdefg");
  	$this->assertEquals(Bitcoin::remove0x("0Xabcdefg"), "abcdefg");
  }
  /**
   * Test the Bitcoin::privKeyToWIF() 
   */
  public function testPrivKeyToWIF() {
    # examples from https://en.bitcoin.it/wiki/Wallet_import_format
    $this->assertEquals(Bitcoin::privKeyToWIF("0C28FCA386C7A227600B2FE50B7CAE11EC86D3BF1FBE471BE89827E19D72AA1D"), '5HueCGU8rMjxEXxiPuD5BDku4MkFqeZyd4dZ1jvhTVqvbTLvyTJ');
  }
  /**
   * Test the Bitcoin::WIFToPrivKey()
   */
  public function testWIFToPrivKey() {
    # examples from https://en.bitcoin.it/wiki/Wallet_import_format
    $this->assertEquals(Bitcoin::WIFToPrivKey('5HueCGU8rMjxEXxiPuD5BDku4MkFqeZyd4dZ1jvhTVqvbTLvyTJ'), "0C28FCA386C7A227600B2FE50B7CAE11EC86D3BF1FBE471BE89827E19D72AA1D");
  }
}
?>
