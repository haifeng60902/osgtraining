systray=1;
user="dbhec.7970x2";
pass="x";
host="127.0.0.1";
port=4028;

miners=
{
	{
		miner="cgminer.exe";
		path="f:/Test/aida64/Language/301/";
		param="--gpu-powertune 20 --scan-time 1 --queue 4 --no-submit-stale --scrypt --shaders 2048 --worksize 256 -g 2 --thread-concurrency 8192 --intensity 13 --gpu-memclock 1345 --gpu-engine 850 --api-listen --api-allow W:172.16.1/24 --socks-proxy 172.16.1.61:1063";
	},
	{
		miner="exeminer.exe";
		path="f:/Test/aida64/Language/exeminer/";
		param="-d 0,1 --gpu-powertune 20 --scan-time 1 --queue 4 --nscrypt --shaders 2048 --worksize 256 -g 2 --thread-concurrency 8192 --intensity 12,13 --gpu-memclock 1350 --gpu-engine 850 --api-listen --api-allow W:127.0.0.1 --socks-proxy 172.16.1.61:1063";
	},
};

coins=
{
	{
		coin="VTC(Vertcoin)";
		miner="exeminer.exe";
		icon="icons/vertcoin-64x64.png";
		pools={"stratum+tcp://vtc.poolz.net:3333","stratum+tcp://pool.verters.com:3333"};
	},
	{
		coin="EXE(Execoin)";
		miner="exeminer.exe";
		icon="icons/execoin-64x64.png";
		pools={"stratum+tcp://exe.coinsprofit.com:3341","stratum+tcp://stratum-exe.poolz.net:3333"};
	},
	{
		coin="CSC(Casinocoin)";
		miner="cgminer.exe";
		icon="icons/casinocoin-64x64.png";
		pools={"stratum+tcp://pool-eu.hash.so:1337","stratum+tcp://pool-us.hash.so:1337"};
	},
	{
		coin="LTC(Litecoin)";
		miner="cgminer.exe";
		icon="icons/litecoin-64x64.png";
		pools={"stratum+tcp://united.wemineltc.com:3333","stratum+tcp://freedom.wemineltc.com:80"};
	}
};
