<?php

namespace bitcoin\bitcoinphp;

/**
 * Exception class for BitcoinClient
 *
 * @author Mike Gogulski
 * 	http://www.gogulski.com/ http://www.nostate.com/
 */
class BitcoinClientException extends \ErrorException {
  // Redefine the exception so message isn't optional
  public function __construct($message, $code = 0, $severity = E_USER_NOTICE, Exception $previous = null) {
    parent::__construct($message, $code, $severity, $previous);
  }

  public function __toString() {
    return __CLASS__ . ": [{$this->code}]: {$this->message}\n";
  }
}
