<?php

require_once dirname(__FILE__) . '/../bitcoin.inc';

/**
 * Test class for BitcoinClient.
 *
 * By Mike Gogulski - All rights reversed - http://www.unlicense.org/ (public domain)
 *
 * @author Mike Gogulski - http://www.nostate.com/ http://www.gogulski.com/
 */
class BitcoinClientTest extends PHPUnit_Framework_TestCase {
  var $c = NULL;

  protected function setUp() {
    if (true && !extension_loaded("curl"))
      dl("php_curl.dll");//retardation on my PHP/Win7 install
    if (!$this->c)
      $this->c = new BitcoinClient("https", "fnordbagger", "spambots", "nobody.local", 8332, 'd:\xampp\php\server.cert', 0);
  }

  protected function tearDown() {
  }

  /**
   * @expectedException BitcoinClientException
   */
  public function testInvalidScheme() {
    $junk = new BitcoinClient("ftp", "bobo", "mypass", "kremvax.kremlin.su");
  }

  /**
   * @expectedException BitcoinClientException
   */
  public function testNoUsername() {
    $junk = new BitcoinClient("http", "", "mypass", "kremvax.kremlin.su");
  }

  /**
   * @expectedException BitcoinClientException
   */
  public function testNoPassword() {
    $junk = new BitcoinClient("https", "bobo", "", "kremvax.kremlin.su");
  }

  /**
   * @expectedException BitcoinClientException
   */
  public function testNoAddress() {
    $junk = new BitcoinClient("https", "bobo", "", "kremvax.kremlin.su");
  }

  /**
   * @expectedException BitcoinClientException
   */
  public function testInvalidPortString() {
    $junk = new BitcoinClient("http", "bobo", "mypass", "kremvax.kremlin.su", "yeehaw");
  }

  /**
   * @expectedException BitcoinClientException
   */
  public function testInvalidPortFloat() {
    $junk = new BitcoinClient("https", "bobo", "mypass", "kremvax@kremlin.su", 3.14159);
  }
  /**
   * @expectedException BitcoinClientException
   */
  public function testInvalidPortNegative() {
    $junk = new BitcoinClient("http", "bobo", "mypass", "kremvax@kremlin.su", -273);
  }
  /**
   * @expectedException BitcoinClientException
   */
  public function testInvalidPortPositive() {
    $junk = new BitcoinClient("https", "bobo", "mypass", "kremvax@kremlin.su", 65536);
  }

  /**
   * @expectedException BitcoinClientException
   */
  public function testUnreadableCertificate() {
    $junk = new BitcoinClient("http", "bobo", "mypass", "kremvax@kremlin.su", 8332, "/doesntexist.cert");
  }

  public function testgetaddress() {
    $this->assertTrue(Bitcoin::checkAddress($this->c->getnewaddress()));
  }

  public function testgetaddressWithLabel() {
    $address = $this->c->getnewaddress("test label");
    $this->assertTrue(Bitcoin::checkAddress($address));
    $this->assertEquals($this->c->getlabel($address), "test label");
  }

  public function testCan_connect() {
    $this->assertTrue($this->c->can_connect());
  }

  public function testQuery_arg_to_parameter() {
    $this->assertEquals($this->c->query_arg_to_parameter("string"), new jsonrpcval("string"));
    $this->assertEquals($this->c->query_arg_to_parameter("string with spaces"), new jsonrpcval("string with spaces"));
    $this->assertEquals($this->c->query_arg_to_parameter(3), new jsonrpcval(3, "int"));
    $this->assertEquals($this->c->query_arg_to_parameter(3.14159), new jsonrpcval(3.14159, "double"));
    $this->assertEquals($this->c->query_arg_to_parameter("3"), new jsonrpcval(3, "int"));
    $this->assertEquals($this->c->query_arg_to_parameter("3.14159"), new jsonrpcval(3.14159, "double"));
    $this->assertEquals($this->c->query_arg_to_parameter(TRUE), new jsonrpcval(TRUE, "boolean"));
    $this->assertEquals($this->c->query_arg_to_parameter(array("fnord")), new jsonrpcval(array("fnord"), "array"));
  }

  public function testBackupwallet() {
    @unlink("G:/tmp/wallet.dat");
    $this->assertEquals($this->c->backupwallet("/tmp/wallet.dat"), '');
    @unlink("G:/tmp/wallet.dat");
  }

  /**
   * @expectedException BitcoinClientException
   */
  public function testBackupwalletBad1() {
    touch("G:/tmp/wallet.dat");
    $this->c->backupwallet("/tmp/wallet.dat");
    @unlink("G:/tmp/wallet.dat");// NOTREACHED
  }

  /**
   * @expectedException BitcoinClientException
   */
  public function testBackupwalletBad2() {
    $this->c->backupwallet("/tmpqoxxx/wallet.dat");
  }

  /**
   * @todo Add tests for getbalance(account, minconf)
   */
  public function testGetbalance() {
    $this->assertInternalType("float", $this->c->getbalance());
  }

  public function testGetblockcount() {
    $this->assertInternalType("int", $this->c->getblockcount());
  }

  public function testGetblocknumber() {
    $this->assertInternalType("int", $this->c->getblocknumber());
  }

  public function testGetconnectioncount() {
    $this->assertInternalType("int", $this->c->getconnectioncount());
  }

  public function testGetdifficulty() {
    $this->assertInternalType("float", $this->c->getdifficulty());
  }

  public function testSetGetgenerate() {
    $this->assertEquals($this->c->setgenerate(TRUE, 1), '');
    $this->assertTrue($this->c->getgenerate());
    $this->assertEquals($this->c->setgenerate(FALSE, 0), '');
    $this->assertFalse($this->c->getgenerate());
  }

  public function testGetinfo() {
    $this->assertInternalType("array", $ret = $this->c->getinfo());
    $this->assertArrayHasKey("version", $ret);
    $this->assertInternalType("int", $ret["version"]);
  }

  /**
   * @since 0.3.17
   * @todo implement
   */
  public function testGetaccount() {
    $this->markTestIncomplete();
  }

  /**
   * @deprecated Since 0.3.17
   */
  public function testLabel() {
    $stamp = md5(strval(time));
    $address = $this->c->getnewaddress();
    $this->assertEquals($this->c->setlabel($address, $stamp), '');
    $this->assertEquals($this->c->getlabel($address), $stamp);
    $this->assertEquals($this->c->getreceivedbylabel($stamp, 0), 0.00);
    $this->assertEquals($this->c->setlabel($address, ''), '');
    $this->assertEquals($this->c->getlabel($address), '');
  }

  /**
   * @since 0.3.17
   * @todo implement
   */
  public function testSetaccount() {
    $this->markTestIncomplete();
  }

  public function testGetreceivedbyaddress() {
    try {
      $this->assertEquals($this->c->getreceivedbyaddress("1Mnu2THcNAjd1diBJ79mhTXCxPeG3K6mLU"), 1.00);
    } catch (Exception $e) {
      do {
        printf("%s:%d %s (%d) [%s]\n", $e->getFile(), $e->getLine(), $e->getMessage(), $e->getCode(), get_class($e));
      } while ($e = $e->getPrevious());
    }
    $this->assertEquals($this->c->getreceivedbyaddress("1Mnu2THcNAjd1diBJ79mhTXCxPeG3K6mLU"), 1.00);
    $this->assertEquals($this->c->getreceivedbyaddress("1Kr7USMAgMo7fcPSWsQ7kGL12V3u4sNtjV"), 0.00);
  }

  /**
   * @since 0.3.17
   * @todo implement
   */
  public function testGetreceivedbyaccount() {
    $this->markTestIncomplete();
  }

  public function testHelp($command = NULL) {
    $this->assertInternalType("string", $ret = $this->c->help());
  }

  public function testListreceivedbyaddress() {
    $this->assertInternalType("array", $ret = $this->c->listreceivedbyaddress());
  }

  /*
   * @since 0.3.17
   * @todo implement
   */
  public function testListreceivedbyaccount() {
    $this->markTestIncomplete();
  }

  /**
   * @deprecated Since 0.3.17
   */
  public function testListreceivedbylabel() {
    $this->assertInternalType("array", $ret = $this->c->listreceivedbylabel());
  }

  /**
   * @todo Implement
   */
  public function testSendtoaddress() {
    $this->markTestIncomplete();
  }

  /**
   * @todo Implement?
   */
  public function testStop() {
    $this->markTestIncomplete();
  }

  public function testValidateaddress() {
	$junk = $this->c->validateaddress('1Kr7USMAgMo7fcPSWsQ7kGL12V3u4sNtjV');
    $this->assertTrue($junk["isvalid"]);
    $junk = $this->c->validateaddress('1F417eczAAbh41V4oLGNf3DqXLY72hsM73');
    $this->assertTrue($junk["isvalid"]);
    $junk = $this->c->validateaddress('1F417eczAAbh41V4oLGNf3DqXLY72hsM7');
    $this->assertFalse($junk["isvalid"]);
    $junk = $this->c->validateaddress('fnordbarbaz');
    $this->assertFalse($junk["isvalid"]);
  }

  /**
   * @todo Implement
   * @since 0.3.18
   */
  public function testGettransaction() {
    $this->markTestIncomplete();
  }

  /**
   * @todo Implement
   * @since 0.3.18
   */
  public function testMove() {
    $this->markTestIncomplete();
  }

  /**
   * @todo Implement
   * @since 0.3.18
   */
  public function testSendfrom() {
    $this->markTestIncomplete();
  }

  /**
   * @todo This is a bit weak...
   * @since 0.3.18
   */
  public function testGetwork() {
    $this->junk = $this->c->getwork();
    $this->assertArrayHasKey("midstate", $this->junk);
    $this->assertArrayHasKey("data", $this->junk);
    $this->assertArrayHasKey("hash1", $this->junk);
    $this->assertArrayHasKey("target", $this->junk);
  }

  /**
   * @todo Implement
   * @since 0.3.18
   */
  public function testGetaccountaddress() {
    $this->markTestIncomplete();
  }

  /**
   * @todo Implement
   */
  public function testGethashespersec() {
    $this->markTestIncomplete();
  }

  /**
   * @todo Implement
   * @since 0.3.18
   */
  public function testGetaddressesbyaccount() {
    $this->markTestIncomplete();
  }

}
?>