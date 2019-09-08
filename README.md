## Wonder Trade

This adds Wonder Trades to Fire Red.

The NPC trainers are used as the source of these Pokémon; you might end up with Blaine's Rapidash, for example, complete with Blaine's OTID and OT Name and custom moveset.

### Build Instructions

See [here](https://gist.github.com/Zeturic/db1611cc7b17c3140f9b9af32e1b596b) for the prequisites and help in installing them.

Once you've done that, make sure you've added [dtan](https://github.com/zeturic/bpre-dtan) to your ROM.

#### Cloning the repo and building the tools

Open your terminal to whatever folder you want to download this repo into. Then, do the following to download the repo and build the included tools:

```shell
$ git clone https://github.com/Zeturic/bpre-wonder-trade.git
$ cd bpre-wonder-trade
$ ./build_tools.sh
```

#### Adding your ROM

Copy your ROM to this directory and rename it `rom.gba`.

#### Configuration

##### Compile Time Constants

Open `config.mk` in a text editor to set some compile-time configuration.

The build system is smart enough to find enough free space on its own, but if you want it to be inserted at a particular address, you can specify it by updating the definition of `START_AT`.

If the given address is acceptable (i.e. is word-aligned and has enough bytes of free space), it will be inserted there. Otherwise, it will just use `START_AT` to determine where in the ROM it should start looking for free space.

The code to select a random Pokémon gets registered so that it can be used with `special2` / `specialvar` in scripts. Naturally, you will need an unused special id. It defaults to `0x151` which is unused by default, but if that doesn't work for you, you can modify `SPECIAL_WonderTradeGenerateMon` to whatever you want.

An example script showing off how to use the new special to create a working Wonder Trade script is included in this repo, but it isn't built or inserted into the ROM by default. If you want it, set `INSERT_EXAMPLE_SCRIPT` to `true`.

##### Wonder Trade Script

If you're comfortable with decomp-style scripts, you can modify the example script itself contained in `data/scripts/wonder_trade.inc`. But, again, regardless of what changes you make to it, it won't be built unless you set `INSERT_EXAMPLE_SCRIPT` to `true` in `config.mk`.

##### Wonder Trade Trainer Blacklist

If there are specific trainers you'd like to exclude from the Wonder Trade pool, you can set up your blacklist by adding entries to `gWonderTradeTrainerBlacklist` in `src/wonder_trade_blacklist.c`. For example, if you wanted to exclude Brock (trainer number `414`):

```C
const u8 gWonderTradeTrainerBlacklist[TRAINERS_COUNT] =
{
    BLACKLIST_TRAINER(0),
    BLACKLIST_TRAINER(414),
};
```

#### Building the project itself

Once you're ready, run:

```shell
$ make
```

This won't actually modify `rom.gba`, instead your output will be in `test.gba`.

Also, for future reference, you'll probably want to check where it inserted `gWonderTradeTrainerBlacklist` and `WonderTradeScript` with:

```shell
$ cat test.sym | grep "gWonderTradeTrainerBlacklist\|WonderTradeScript"
```

### Usage

#### How do I use the example script?

You'll need to know where `WonderTradeScript` was inserted when this was first built (see above). Then, you can just apply that to a person/signpost event in AdvanceMap.

Obviously, you can't use the example script if you didn't build/insert it.

#### How do I write my own script with XSE?

As mentioned above, this is set up for use with `special2`.

`special2` is a variant of `special` used for returning values; this is used because it's not actually guaranteed that it will be able to find a Pokémon. If the majority of NPC trainers are excluded from the WT pool - whether because they're blacklisted or because their name is too long (see below) - and the player simply gets unlucky, it might take a while to find a suitable trainer randomly.

While such a scenario is admittedly very unlikely, it's avoided entirely because it gives up after a certain number of attempts, and a script will naturally need to know whether it was successful in finding a trainer and Pokémon or not. The variable supplied to `special2` will be set to `0` if it failed, or `1` if it was successful.

Aside from that, the other important part of a script is the trade itself. You can do the trade (including the trade animation) with `special 0xFE`. The party slot of the Pokémon the player is trading should be placed on variable `0x8005` before doing `special 0xFE`.

Assuming you kept `SPECIAL_WonderTradeGenerateMon` as `0x151`, a minimal XSE script for a WT would look like:

```
#org @Main
  setvar 0x8005 0
  special2 LASTRESULT 0x151
  compare LASTRESULT 0
  if 0x1 goto @DoNothing
  special 0xFE
  end

#org @DoNothing
  end
```

#### How do I modify my WT blacklist later on?

You'll need to know where `gWonderTradeTrainerBlacklist` was inserted when this was first built (see above).

`gWonderTradeTrainerBlacklist` is set up to be easy to modify in a hex editor. Every trainer has a corresponding entry in the table, and each entry is a byte long and will be either `00` if the trainer is not blacklisted or `FF` if they are.

For example, if you wanted to blacklist Misty (trainer number `415`), you'd set the byte at `gWonderTradeTrainerBlacklist + 415` to `FF`.

### Caveats

* You could end up with a Nat'l Dex Pokémon early. You'll probably want to enable foreign Pokémon trading and evolution, assuming you aren't simply giving out the Nat'l Dex at the beginning of the game.
* Some NPC trainers such as Giovanni have names that are too long to fit in a Pokémon's OT Name field. These trainers are excluded from the pool.
* Any Pokémon that isn't included in a team of an eligible trainer can't be received at all.
* It is possible to get the same Pokémon multiple times.
* You'll probably trade with a lot of people named GRUNT unless you blacklist all the GRUNT trainers.

### Credits

Project structure, `preproc`, and `scaninc` are all from [pokeemerald](https://github.com/pret/pokeemerald).
