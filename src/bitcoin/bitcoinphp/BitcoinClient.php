<?php

namespace bitcoin\bitcoinphp;

use Graze\Guzzle\JsonRpc\JsonRpcClientInterface;


class BitcoinClient {

  private $client;

  public function __construct(JsonRpcClientInterface $client) {
    $this->client = $client;
    $this->getInfo();
  }
  
  public static function URI($scheme, $username, $password, $hostname, $port) {
    return $scheme . '://' . rawurlencode($username) . ':' . rawurlencode($password) . '@' . rawurlencode($hostname) . ':' . (int) $port;
  }

  public function request($method, $params = array()) {
    return $this->client->request($method, 1, $params)->send()->getResult();
  }
  
  /**
   * Adds a nrequired-to-sign multisignature address to the wallet.
   *
   * Each key is a bitcoin address or hex-encoded public key. If $account is
   * specified, assigns address to $account.
   *
   * @param $nrequired
   * @param $keys
   * @param $account
   *
   * @command addmultisigaddress
   */
  public function addMultiSigAddress($nrequired, $keys, $account = NULL) {
    $this->request('addmultisigaddress', array($nrequired, $keys, $account));
  }
  
  /**
   * Attempts add or remove $node from the addnode list or try a connection to
   * $node once.
   *
   * @param $node
   * @param $type
   *   add/remove/onetry
   *
   * @command addnode
   * @requires version 0.8
   */
  public function addNode($node, $type) {
    $this->request('addnode', array($node, $type));
  }

  /**
   * Safely copies wallet.dat to destination, which can be a directory or a path
   * with filename.
   *
   * @param <destination>
   *
   * @command backupwallet
   */
  public function backupWallet($destination) {
    $this->request('backupwallet', array($destination));
  }

  /**
   * Creates a multi-signature address and returns a json object.
   *
   * @param $nrequired
   * @param $keys
   *
   * @command createmultisig
   */
  public function createMultiSig($nrequired, $keys) {
    return $this->request('createmultisig', array($nrequired, $keys));
  }

  /**
   * Creates a raw transaction spending given inputs.
   *
   * @param $inputs
   *   [{"txid":txid,"vout":n},...]
   * @param $outputs
   *   {address:amount,...}
   *
   * @requires version 0.7
   * @command createrawtransaction
   */
  public function createRawTransaction($inputs, $outputs) {
    return $this->request('createrawtransaction', array($inputs, $outputs));
  }

  /**
   * Produces a human-readable JSON object for a raw transaction.
   *
   * @param $raw_transaction
   *   <hex string>
   *
   * @command decoderawtransaction
   * @requires version 0.7
   */
  public function decodeRawTransaction($raw_transaction) {
    return $this->request('decoderawtransaction', array($raw_transaction));
  }

  /**
   * Reveals the private key corresponding to an address.
   *
   * @param $address
   *
   * @command dumpprivkey
   * @requires Unlocked wallet
   */
  public function dumpPrivKey($address) {
    return $this->request('dumpprivkey', array($address));
  }

  /**
   * Encrypts the wallet with a passphrase.
   *
   * @param $passphrase
   *
   * @command encryptwallet
   */
  public function encryptWallet($passphrase) {
    return $this->request('encryptwallet', array($passphrase));
  }

  /**
   * Returns the account associated with an address.
   *
   * @param $address
   *
   * @command getaccount
   */
  public function getAccount($address) {
    return $this->request('getaccount', array($address));
  }

  /**
   * Returns the current bitcoin address for receiving payments to an account.
   *
   * @param $account
   *
   * @command getaccountaddress
   */
  public function getAccountAddress($account) {
    return $this->request('getaccountaddress', array($account));
  }

  /**
   * getaddednodeinfo
   *
   * @param <dns>
   * @param [node]
   *
   * version 0.8 Returns information about the given added node, or all added
   * nodes (note that onetry addnodes are not listed here) If dns is false, only
   * a list of added nodes will be provided, otherwise connected information
   * will also be available.
   */
  public function getAddedNodeInfo($dns, $node = NULL) {
    return $this->request('getaddednodeinfo', array($dns, $node));
  }

  /**
   * getaddressesbyaccount
   *
   * @param $account
   *
   * Returns the list of addresses for the given account.
   */
  public function getAddressesByAccount($account) {
    return $this->request('getaddressesbyaccount', array($account));
  }

  /**
   * getbalance
   *
   * @param $account
   * @param $minconf
   *
   * If [account] is not specified, returns the server's total available
   * balance. If [account] is specified, returns the balance in the account.
   */
  public function getBalance($account = '', $minconf = 1) {
    return $this->request('getbalance', array($account, $minconf));
  }

  /**
   * getbestblockhash
   *
   * recent git checkouts only Returns the hash of the best (tip) block in the
   * longest block chain.
   */
  public function getBestBlockHash() {
    return $this->request('getbestblockhash');
  }

  /**
   * getblock
   *
   * @param $hash
   *
   * Returns information about the block with the given hash.
   */
  public function getBlock($hash) {
    return $this->request('getblock', array($hash));
  }

  /**
   * getblockcount
   *
   * Returns the number of blocks in the longest block chain.
   */
  public function getBlockCount() {
    return $this->request('getblockcount');
  }

  /**
   * getblockhash
   *
   * @param $index
   *
   * Returns hash of block in best-block-chain at <index>; index 0 is the
   * genesis block
   */
  public function getBlockHash($index) {
    return $this->request('getblockhash', array($index));
  }

  /**
   * getblocktemplate
   *
   * @param $params
   *
   * Returns data needed to construct a block to work on. See BIP_0022 for more
   * info on params.
   */
  public function getBlockTemplate($params) {
    return $this->request('getblocktemplate', array($params));
  }

  /**
   * getconnectioncount
   *
   * Returns the number of connections to other nodes.
   */
  public function getConnectionCount() {
    return $this->request('getconnectioncount');
  }

  /**
   * getdifficulty
   *
   * Returns the proof-of-work difficulty as a multiple of the minimum
   * difficulty.
   */
  public function getDifficulty() {
    return $this->request('getdifficulty');
  }

  /**
   * getgenerate
   *
   * Returns true or false whether bitcoind is currently generating hashes.
   */
  public function getGenerate() {
    return $this->request('getgenerate');
  }

  /**
   * gethashespersec
   *
   * Returns a recent hashes per second performance measurement while
   * generating.
   */
  public function getHashesPerSec() {
    return $this->request('gethashespersec');
  }

  /**
   * getinfo
   *
   * Returns an object containing various state info.
   */
  public function getInfo() {
    return $this->request('getinfo');
  }

  /**
   * getmininginfo
   *
   * Returns an object containing mining-related information:
   *   - blocks
   *   - currentblocksize
   *   - currentblocktx
   *   - difficulty
   *   - errors
   *   - generate
   *   - genproclimit
   *   - hashespersec
   *   - pooledtx
   *   - testnet 
   *
   * N
   */
  public function getMiningInfo() {
    return $this->request('getmininginfo');
  }

  /**
   * getnewaddress
   *
   * @param $account
   *
   * Returns a new bitcoin address for receiving payments. If [account] is
   * specified (recommended), it is added to the address book so payments
   * received with the address will be credited to [account].
   */
  public function getNewAddress($account = NULL) {
    return $this->request('getnewaddress', $account);
  }

  /**
   * getpeerinfo
   *
   * version 0.7 Returns data about each connected node.
   */
  public function getPeerInfo() {
    return $this->request('getpeerinfo');
  }

  /**
   * getrawchangeaddress
   *
   * @param $account
   *
   * recent git checkouts only Returns a new Bitcoin address, for receiving
   * change. This is for use with raw transactions, NOT normal use. 	Y
   */
  public function getRawChangeAddress($account = NULL) {
    return $this->request('getrawchangeaddress', array($account));
  }

  /**
   * getrawmempool
   *
   * version 0.7 Returns all transaction ids in memory pool
   */
  public function getRawMemPool() {
    return $this->request('getrawmempool');
  }

  /**
   * getrawtransaction
   *
   * @param $txid
   * @param $verbose
   *
   * version 0.7 Returns raw transaction representation for given transaction
   * id.
   */
  public function getRawTransaction($txid, $verbose = 0) {
    return $this->request('getrawtransaction', array($txid, $verbose));
  }

  /**
   * getreceivedbyaccount
   *
   * @param $account
   * @param $minconf
   *
   * Returns the total amount received by addresses with [account] in
   * transactions with at least [minconf] confirmations. If [account] not
   * provided return will include all transactions to all accounts.
   * (version 0.3.24)
   */
  public function getReceivedByAccount($account = NULL, $minconf = 1) {
    return $this->request('getreceivedbyaccount', array($account, $minconf));
  }

  /**
   * getreceivedbyaddress
   *
   * @param $address
   * @param $minconf
   *
   * Returns the amount received by <bitcoinaddress> in transactions with at
   * least [minconf] confirmations. It correctly handles the case where someone
   * has sent to the address in multiple transactions. Keep in mind that
   * addresses are only ever used for receiving transactions. Works only for
   * addresses in the local wallet, external addresses will always show 0.
   */
  public function getReceivedByAddress($address, $minconf = 1) {
    return $this->request('getreceivedbyaddress', array($address, $minconf));
  }

  /**
   * gettransaction
   *
   * @param $txid
   *
   * Returns an object about the given transaction containing:

    "amount" : total amount of the transaction
    "confirmations" : number of confirmations of the transaction
    "txid" : the transaction ID
    "time" : time associated with the transaction[1].
    "details" - An array of objects containing:
        "account"
        "address"
        "category"
        "amount"
        "fee" 

	N
   */
  public function getTransaction($txid) {
    return $this->request('gettransaction', array($txid));
  }

  /**
   * gettxout
   * 
   * @param $txid
   * @param $n
   * @param $includemempool
   *
   * Returns details about an unspent transaction output (UTXO)
   */
  public function getTxOut($txid, $n, $includemempool = TRUE) {
    return $this->request('gettxout', array($txid, $n));//, $includemempool));
  }

  /**
   * gettxoutsetinfo
   *
   * Returns statistics about the unspent transaction output (UTXO) set
   */
  public function getTxOutSetInfo() {
    return $this->request('gettxoutsetinfo');
  }

  /**
   * getwork
   *
   * $data
   *
   * If [data] is not specified, returns formatted hash data to work on:

    "midstate" : precomputed hash state after hashing the first half of the data
    "data" : block data
    "hash1" : formatted hash buffer for second hash
    "target" : little endian hash target 

If [data] is specified, tries to solve the block and returns true if it was successful.
	N
   */
  public function getWork($data = NULL) {
    return $this->request('getwork', array($data));
  }

  /**
   * help
   *
   * [command]
   *
   * List commands, or get help for a command.
   */
  public function help($command = NULL) {
    return $this->request('help');
  }

  /**
   * importprivkey
   *
   * @param $privkey
   * @param $label
   * @parma $rescan
   *
   * Adds a private key (as returned by dumpprivkey) to your wallet. This may
   * take a while, as a rescan is done, looking for existing transactions.
   * Optional [rescan] parameter added in 0.8.0. 	Y
   */
  public function importPrivKey($privkey, $label = NULL, $rescan = TRUE) {
    $this->request('importprivkey', array($privkey, $label, $rescan));
  }

  /**
   * keypoolrefill
   *
   * Fills the keypool, requires wallet passphrase to be set. 	Y
   */
  public function keypoolRefill() {
    $this->request('keypoolrefill');
  }

  /**
   * listaccounts
   *
   * @param $minconf
   *
   * Returns Object that has account names as keys, account balances as values.
   * N
   */
  public function listAccounts($minconf = 1) {
    return $this->request('listaccounts', array($minconf));
  }

  /**
   * Returns all addresses in the wallet and info used for coincontrol.
   *
   * listaddressgroupings
   *
   * version 0.7 
   */
  public function listAddressGroupings() {
    return $this->request('listaddressgroupings');
  }

  /**
   * listreceivedbyaccount
   *
   * @param $minconf
   * @param $includeempty
   *
   * @return 	Returns an array of objects containing:

    "account" : the account of the receiving addresses
    "amount" : total amount received by addresses with this account
    "confirmations" : number of confirmations of the most recent transaction included 

	N
   */
  public function listReceivedByAccount($minconf = 1, $includeempty = FALSE) {
    return $this->request('listreceivedbyaccount', array($minconf, $includeempty));
  }

  /**
   * listreceivedbyaddress
   *
   * @param $minconf
   * @param $includeempty
   *
   * @return An array of objects containing:

    "address" : receiving address
    "account" : the account of the receiving address
    "amount" : total amount received by the address
    "confirmations" : number of confirmations of the most recent transaction included 

To get a list of accounts on the system, execute bitcoind listreceivedbyaddress 0 true
	N
   */
  public function listReceivedByAddress($minconf = 1, $includeempty = FALSE) {
    return $this->request('listreceivedbyaddress', array($minconf, $includeempty));
  }

  /**
   * Get all transactions in blocks since block [blockhash], or all transactions
   * if omitted.
   *
   * listsinceblock
   *
   * @param $blockhash
   * @param $target_confirmations
   *   Ignored (bug) up to (at least) v0.8.5
   *
   * N
   */
  public function listSinceBlock($blockhash = NULL, $target_confirmations = NULL) {
    return $this->request('listsinceblock', array($blockhash , $target_confirmations));
  }

  /**
   * listtransactions
   *
   * $param $account
   * $param $count
   * $param $from
   *
   * Returns up to [count] most recent transactions skipping the first [from]
   * transactions for account [account]. If [account] not provided will return
   * recent transaction from all accounts.
   */
  public function listTransactions($account = '', $count = 10, $from = 0) {
    return $this->request('listtransactions', array($account, $count, $from));
  }

  /**
   * Returns array of unspent transaction inputs in the wallet.
   *
   * listunspent
   *
   * @param $minconf
   * @param $maxconf
   *
   * @requires version 0.7
   * N
   */
  public function listUnspent($minconf = 1, $maxconf = 999999) {
    return $this->request('listunspent', array($minconf, $maxconf));
  }

  /**
   * Returns list of temporarily unspendable outputs.
   *
   * listlockunspent
   * @requires version 0.8 
   */
  public function listLockUnspent() {
    return $this->request('listlockunspent');
  }

  /**
   * Updates list of temporarily unspendable outputs.
   *
   * $param $unlock
   * $param $outputs
   *
   * lockunspent
   * @requires version 0.8
   */
  public function lockUnspent($unlock, $outputs) {
    $this->request('lockunspent', array($unlock, $outputs));
  }

  /**
   * Moves from one account in your wallet to another.
   *
   * @param $fromaccount
   * @param $toaccount
   * @param $amount
   * @param $minconf
   * @param $comment
   *
   *
   
   * @command move
   */
  public function move($from_account, $to_account, $amount, $minconf = 1, $comment = NULL) {
    $this->request('move', array($from_account, $to_account, $amount, $minconf, $comment));
  }

  /**
   * sendfrom 	<fromaccount> <tobitcoinaddress> <amount> [minconf=1] [comment] [comment-to] 	<amount> is a real and is rounded to 8 decimal places. Will send the given amount to the given address, ensuring the account has a valid balance using [minconf] confirmations. Returns the transaction ID if successful (not in JSON object). 	Y
   */
  public function sendFrom($from_account, $to_address, $amount, $minconf = 1, $comment = NULL, $comment_to = NULL) {
    return $this->request('sendfrom', array($from_account, $to_address, $amount, $minconf, $comment, $comment_to));
  }

  /**
   * sendmany 	<fromaccount> {address:amount,...} [minconf=1] [comment] 	amounts are double-precision floating point numbers 	Y
   */
  public function sendMany($from_account, $addresses, $minconf = 1, $comment = NULL) {
    return $this->request('sendmany', array($from_account, $addresses, $minconf, $comment));
  }

  /**
   * sendrawtransaction 	<hexstring> 	version 0.7 Submits raw transaction (serialized, hex-encoded) to local node and network.
   *
   * @return string
   *   Transaction ID.
   */
  public function sendRawTransaction($raw_transaction) {
    return $this->request('sendrawtransaction', array($raw_transaction));
  }

  /**
   * sendtoaddress 	<bitcoinaddress> <amount> [comment] [comment-to] 	<amount> is a real and is rounded to 8 decimal places. Returns the transaction ID <txid> if successful. 	Y
   */
  public function sendToAddress($address, $amount, $comment = NULL, $comment_to = NULL) {
    return $this->request('sendtoaddress', array($address, $amount, $comment, $comment_to));
  }

  /**
   * setaccount 	<bitcoinaddress> <account> 	Sets the account associated with the given address. Assigning address that is already assigned to the same account will create a new address associated with that account.
   */
  public function setAccount($address, $amount) {
    $this->request('setaccount', array($address, $amount));
  }

  /**
   * setgenerate 	<generate> [genproclimit] 	<generate> is true or false to turn generation on or off.
Generation is limited to [genproclimit] processors, -1 is unlimited.
   */
  public function setGenerate($generate, $gen_proc_limit = NULL) {
    $this->request('setgenerate', array($generate, $gen_proc_limit));
  }

  /**
   * settxfee 	<amount> 	<amount> is a real and is rounded to the nearest 0.00000001
   */
  public function setTxFee($amount) {
    $this->request('settxfee', array($amount));
  }

  /**
   * signmessage 	<bitcoinaddress> <message> 	Sign a message with the private key of an address. 	Y
   */
  public function signMessage($address, $message) {
    return $this->request('signmessage', array($address, $message));
  }

  /**
   * signrawtransaction 	<hexstring> [{"txid":txid,"vout":n,"scriptPubKey":hex},...] [<privatekey1>,...] 	version 0.7 Adds signatures to a raw transaction and returns the resulting raw transaction. 	Y/N
   */
  public function signRawTransaction($raw_transaction, $inputs = NULL, $outputs = NULL) {
    return $this->request('signrawtransaction', array($raw_transaction, $inputs, $outputs));
  }

  /**
   * stop 		Stop bitcoin server.
   */
  public function stop() {
    $this->request('stop');
  }

  /**
   * submitblock 	<hex data> [optional-params-obj] 	Attempts to submit new block to network.
   */
  public function submitBlock($block, $params = NULL) {
    $this->request('submitblock', array($block, $params));
  }

  /**
   * validateaddress 	<bitcoinaddress> 	Return information about <bitcoinaddress>.
   */
  public function validateAddress($address) {
    return $this->request('validateaddress', array($address));
  }

  /**
   * verifymessage 	<bitcoinaddress> <signature> <message> 	Verify a signed message.
   */
  public function verifyMessage($address, $signature, $message) {
    return $this->request('verifymessage', array($address, $signature, $message));
  }

  /**
   * walletlock 		Removes the wallet encryption key from memory, locking the wallet. After calling this method, you will need to call walletpassphrase again before being able to call any methods which require the wallet to be unlocked.
   */
  public function walletLock() {
    $this->request('walletlock');
  }

  /**
   * walletpassphrase 	<passphrase> <timeout> 	Stores the wallet decryption key in memory for <timeout> seconds.
   */
  public function walletPassphrase($passphrase, $timeout) {
    $this->request('walletpassphrase', array($passphrase, $timeout));
  }

  /**
   * walletpassphrasechange 	<oldpassphrase> <newpassphrase> 	Changes the wallet passphrase from <oldpassphrase> to <newpassphrase>. 
   */
  public function walletPassphraseChange($old_passphrase, $new_passphrase) {
    $this->request('walletpassphrasechange', array($old_passphrase, $new_passphrase));
  }
   
}
