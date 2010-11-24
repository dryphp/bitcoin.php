<?php

require_once dirname(__FILE__) . '/../bitcoin.inc';

/**
 * Test class for BitcoinClient.
 * @author Mike Gogulski
 */
class BitcoinClientTest extends PHPUnit_Framework_TestCase {
  /**
   * @var BitcoinClient
   */
  protected $invalidScheme;
  protected $noUsername;
  protected $noPassword;
  protected $noAddress;
  protected $invalidPort;
  protected $unreadableCertificate;
  var $allGood = NULL;

  protected function setUp() {
    if (true && !extension_loaded("curl"))
      dl("php_curl.dll");//retardation on my PHP/Win7 install
    if (!$this->allGood)
    	$this->allGood = new BitcoinClient("https", "wordpress", "shoppy", "nobody.local", 8332, 'd:\xampp\php\server.cert');
  }

  protected function tearDown() {
  }

  /**
   * @expectedException BitcoinClientException
   */
  public function testInvalidScheme() {
    $this->invalidScheme = new BitcoinClient("ftp", "bobo", "mypass", "kremvax.kremlin.su");
  }

  /**
   * @expectedException BitcoinClientException
   */
  public function testNoUsername() {
    $this->noUsername = new BitcoinClient("http", "", "mypass", "kremvax.kremlin.su");
  }

  /**
   * @expectedException BitcoinClientException
   */
  public function testNoPassword() {
    $this->noPassword = new BitcoinClient("https", "bobo", "", "kremvax.kremlin.su");
  }

  /**
   * @expectedException BitcoinClientException
   */
  public function testNoAddress() {
    $this->noAddress = new BitcoinClient("https", "bobo", "", "kremvax.kremlin.su");
  }

  /**
   * @expectedException BitcoinClientException
   */
  public function testInvalidPortString() {
    $this->invalidPort = new BitcoinClient("http", "bobo", "mypass", "kremvax.kremlin.su", "yeehaw");
  }

  /**
   * @expectedException BitcoinClientException
   */
  public function testInvalidPortFloat() {
    $this->invalidPort = new BitcoinClient("https", "bobo", "mypass", "kremvax@kremlin.su", 3.14159);
  }
  /**
   * @expectedException BitcoinClientException
   */
  public function testInvalidPortNegative() {
    $this->invalidPort = new BitcoinClient("http", "bobo", "mypass", "kremvax@kremlin.su", -273);
  }
  /**
   * @expectedException BitcoinClientException
   */
  public function testInvalidPortPositive() {
    $this->invalidPort = new BitcoinClient("https", "bobo", "mypass", "kremvax@kremlin.su", 65536);
  }

  /**
   * @expectedException BitcoinClientException
   */
  public function testUnreadableCertificate() {
    $this->unreadableCertificate = new BitcoinClient("http", "bobo", "mypass", "kremvax@kremlin.su", 8332, "/doesntexist.cert");
  }

  public function testgetaddress() {
  	$this->markTestSkipped();
    //$this->allGood->setDebug(2);
    $address = $this->allGood->query("getnewaddress");
    $this->assertTrue(Bitcoin::checkAddress($address));
  }

  public function testgetaddressWithLabel() {
	//$this->markTestSkipped();
    //$this->allGood->setDebug(2);
  	$address = $this->allGood->query("getnewaddress", "test label");
  	$this->assertTrue(Bitcoin::checkAddress($address));
  }

  public function testCan_connect() {
    $this->assertTrue($this->allGood->can_connect());
  }

  public function testQuery_arg_to_parameter() {
  	$this->assertEquals($this->allGood->query_arg_to_parameter("string"), new jsonrpcval("string"));
  	$this->assertEquals($this->allGood->query_arg_to_parameter("string with spaces"), new jsonrpcval("string with spaces"));
  	$this->assertEquals($this->allGood->query_arg_to_parameter(3), new jsonrpcval(3, "int"));
  	$this->assertEquals($this->allGood->query_arg_to_parameter(3.14159), new jsonrpcval(3.14159, "double"));
	$this->assertEquals($this->allGood->query_arg_to_parameter("3"), new jsonrpcval(3, "int"));
  	$this->assertEquals($this->allGood->query_arg_to_parameter("3.14159"), new jsonrpcval(3.14159, "double"));
	$this->assertEquals($this->allGood->query_arg_to_parameter(TRUE), new jsonrpcval(TRUE, "boolean"));
	$this->assertEquals($this->allGood->query_arg_to_parameter(array("fnord")), new jsonrpcval(array("fnord"), "array"));
  }

}
?>
