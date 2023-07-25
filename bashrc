# .bashrc

#Source global definitiaons
# User sperific aliases and functions

env=~/.ssh/agent.env
agent_load_env () { test -f "$env" && . "$env" >| /dev/null ; }
agent_start () {
    (umask 077; ssh-agent >| "$env")
    . "$env" >| /dev/null ; }
agent_load_env

#agent_run_state: 0=agent running w/ key; 1=agent w/o key; 2= agent not running
#agent_run_state=$(ssh-add -l >| /dev/null 2>&1; echo $?)

#if [ ! "$SSH_AUTH_SOCK" ] || [ $agent_run_state = 2 ]; then
#    agent_start
#    ssh-add
#elif [ "$SSH_AUTH_SOCK" ] && [ $agent_run_state = 1 ]; then
#    ssh-add
#fi

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

# User specific aliases and functions
# >>> conda initialize >>>
# !! Contents within this block are managed by 'conda init' !!
__conda_setup="$('/cms/scratch/yjeong/anaconda3/bin/conda' 'shell.bash' 'hook' 2> /dev/null)"
if [ $? -eq 0 ]; then
    eval "$__conda_setup"
else
    if [ -f "/cms/scratch/yjeong/anaconda3/etc/profile.d/conda.sh" ]; then
        . "/cms/scratch/yjeong/anaconda3/etc/profile.d/conda.sh"
    else
        export PATH="/cms/scratch/yjeong/anaconda3/bin:$PATH"
    fi
fi
unset __conda_setup
# <<< conda initialize <<<

#source ~/ROOT/root/bin/thisroot.sh

alias root='root -l'
alias rootb='root -b -q'
alias cms='cmsRun'
alias cmstest='./process_nano.exe xrootd/store/mc/RunIISummer16NanoAODv5/TTJets_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/NANOAODSIM/PUMoriond17_Nano1June2019_102X_mcRun2_asymptotic_v7_ext1-v1 /xrootd_user/yjeong/xrootd/nanoprocessing/2016/processed/ SMS-T1tbs_RPV_mGluino1600_TuneCUETP8M1 flist_outputdir_nanoprocessing_2016.txt'
#alias scram='scram b'
alias edmD='edmDumpEventContent'
alias edmP='edmProveDump'
alias edmF='edmFileUtil -P -f'
alias CMSSWver='scramv1 list CMSSW'
alias cmse='cmsenv'
#alias scramr='scram build ProjectRename'
alias mked='mkedanlzr'
alias cmsm='cmsmake'
alias tb='tbrowser'
alias gitp='git push -u'
alias gitc='git commit -a'
alias gitd='git diff'
alias gitch='git checkout'

#alias du='du -m -h'

alias du='du -sh'
alias df='df -m -h'
alias consub='condor_submit'

#after this line, input "(crab_)filename"

alias crabsub='crab submit =c'
#check running crab_job "crab_taskname"
alias crabstat='crab status -d'

#recieve output root files "crab_taskname"

alias crabget='crab getoutput -d'
#crab kill "crab_taskname"
alias crabkill='crab kill -d'

#merging crab root file is hadd xxxx.root a.root b.root

alias uiT2='xrd cms-t2-se01.sdfarm.kr'
alias sig='cmsenv;cmssw-cc6;cmsenv'
alias workh8='cd $HOME/CMSSW_8_1_0_pre8/src'
alias workh7='cd $HOME/CMSSW_7_4_15/src'
alias workhm='cd $HOME/muonPerf/src'

#alias work800='cd /cms/scratch/$USER/CMSSW_8_0_0/src/nanoprocessing'

alias work1050='cd /cms/scratch/$USER/CMSSW_10_5_0/src'
alias work1060='cd /cms/scratch/$USER/CMSSW_10_6_0/src'
alias work10222='cd /cms/scratch/$USER/CMSSW_10_2_22/src'
#alias skim2016='./skim.exe /xrootd_user/yjeong/xrootd/nanoprocessing/2016/processed 5 rpvfitnbge0'
#alias skim2017='./skim.exe /xrootd_user/yjeong/xrootd/nanoprocessing/2017/processed 5 rpvfitnbge0'
#alias skim2018='./skim.exe /xrootd_user/yjeong/xrootd/nanoprocessing/2018/processed 5 rpvfitnbge0'
#alias work10216='cd /cms/scratch/$USER/CMSSW_10_2_16/src'
alias workgit='cd /cms/home/$USER/muonPerf/src'

alias lsr='ls -rlt'
alias work='cd /cms/scratch/$USER'
alias xrootd='cd /xrootd_user/yjeong/xrootd/'
alias xrootds='cd /xrootd/store/mc/'
alias work8='cd /cms/scratch/$USER/CMSSW_8_1_0_pre8/src'

alias set700='export SCRAM_ARCH=slc7_amd64_gcc700'
alias set530='export SCRAM_ARCH=slc7_amd64_gcc530'
alias voms='voms-proxy-init -voms cms -rfc'
alias das='dasgoclient -query' #dataset=/TTJets*/RunIIFall17NanoAODv5*/NANOAODSIM
alias ln='ln -sf ~/flist'
alias ruciolist='rucio list-rules --account yjeong'
alias ps='ps -u yjeong'
alias ll='ls -lh'
alias utils='utils/tdr --style=note b'
alias nfiles='ls -lh | grep ^- | wc -l'

#alias python='python3'

export PATH=/bin:/usr/bin:/usr/local/bin:/cms/ldap_home/yjeong/tools/fastjet-install/bin:/usr/texbin/:/opt/pdflabs/pdftk/bin/$PATH
export PATH=/cms/ldap_home/yjeong/anaconda3/bin:$PATH

#export PATH=$HOME/.local/bin:/cvmfs/cms-bril.cern.ch/brilconda/bin:$PATH
#export PATH=$HOME/.local/bin:/nfshome0/lumipro/brilconda/bin:$PATH
#export PATH=<brilcondabasedir>/bin:$PATH
#export PATH="/cms/ldap_home/yjeong/brilconda/bin:$PATH"

export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
source /cvmfs/cms.cern.ch/cmsset_default.sh
source /cvmfs/cms.cern.ch/rucio/setup.sh
export RUCIO_USER=yjeong
export RUCIO_ACCOUNT=yjeong
export SCRAM_ARCH=slc7_amd64_gcc700
#export SCRAM_ARCH=slc7_amd64_gcc530
#source /cvmfs/cms.cern.ch/crab3/crab.sh
#source /cvmfs/cms.cern.ch/crab3/crab_standalone.sh
#source /cms/scratch/yjeong/bin/activate

chmod 755 /xrootd_user/yjeong/
#rm -r /tmp/tmp*/

cd /cms/scratch/$USER/
#cd CMSSW_10_5_0/src/RPV/rpv_macros
cd CMSSW_10_5_0/src/nanoprocessing
#cd CMSSW_10_2_22/src/
cmsenv

## rucio command --> without cmsenv
#rucioenv --> only ui20
#voms
#rucio list-rules --account geonmo
# added by Brilconda installer
