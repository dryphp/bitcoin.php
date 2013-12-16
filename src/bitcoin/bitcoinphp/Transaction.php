<?php

namespace bitcoin\bitcoinphp;

class Transaction
{

  protected $amount;
  protected $confirmations;
  protected $blockhash;
  protected $blockindex;
  protected $blocktime;
  protected $txid;
  protected $time;
  protected $timereceived;
  protected $details;
  protected $fee;

  public function __construct(BitcoinClient $client, $txid)
  {
    $info = $client->gettransaction($txid);

    foreach ($info as $key => $value) {
      $this->$key = $value;
    }
  }
}
