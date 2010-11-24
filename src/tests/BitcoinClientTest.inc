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
    //$this->allGood->setDebug(2);
    $address = $this->allGood->query("getnewaddress");
    $this->assertTrue(Bitcoin::checkAddress($address));
  }
  public function testgetaddressWithLabel() {
  	$address = $this->allGood->query("getnewaddress", "test label");
  	$this->assertTrue(Bitcoin::checkAddress($address));
  }

  public function testCan_connect() {
    $this->assertTrue($this->allGood->can_connect());
  }

}
?>
