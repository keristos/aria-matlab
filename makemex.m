echo on

funcs = {
    'aria_init',  
    'arrobot_connect', 
    'arrobot_disconnect', 
    'arloginfo', 
    'arrobot_setvel', 
    'arrobot_setrotvel', 
    'arrobot_getx', 
    'arrobot_gety', 
    'arrobot_getth', 
    'arrobot_stop',
    'arrobot_length',
    'arrobot_width',
    'arrobot_radius',
    'arrobot_getsonarrange',
    'arrobot_getnumsonar',
    'arrobot_getdigin',
    'arrobot_setlatvel',
    'arrobot_getbatteryvoltage',
    'arrobot_getvel',
    'arrobot_getrotvel',
    'arrobot_getlatvel',
    'arrobot_setdeltaheading',
    'arrobot_resetpos'
}

% Unload mex functions etc.  Note, if you add a new mex function below that
% does not match these patterns, add it to this list or a pattern that
% matches it.
clear aria_* arloginfo arrobot_*

 
% Set filenames and options depending on current platform
def = ''
switch computer
    case 'PCWIN'
		ariainstdir = 'C:/Program Files/MobileRobots/Aria'
        ariaclink = '-L. -lariac_vc10_i386'
        arialink = '-L../lib -L../bin -lAriaVC10'
        def = '-DWIN32 -win32'
        ariadll = '../bin/AriaVC10.dll'
    case 'PCWIN64'
		ariainstdir = 'C:/Program Files/MobileRobots/Aria'
        ariaclink = '-L. -lariac_vc10_x64'
        def = '-DWIN32'
        arialink = '-L../lib64 -L../bin64 -lAriaVC10'
        ariadll = '../bin64/AriaVC10.dll'
    case 'GLNX86'
		ariainstdir = '/usr/local/Aria'
        ariaclink = '-L. -lariac'
        arialink = '-L../lib -lAria'
        ariadll = '../lib/libAria.so'
    case 'GLNXA64'
		ariainstdir = '/usr/local/Aria'
        ariaclink = '-L. -lariac'
        arialink = '-L../lib -lAria'
        ariadll = '../lib/libAria.so'
	case 'MACI64'
		disp 'Sorry, not set up for Mac yet. You will need to get ARIA and ariac built on Mac, then edit makemex.m to set the appropriate mex compilation flags under the MACI64 computer type case instead of displaying this message..'
		return
	otherwise
        disp 'error, unrecognized system type. (what kind of computer and OS are you on?)'
        computer
		return
end

% Get ARIA runtime library
eval(['copyfile ' ariadll ' .'])

% Compile all the mex functions:

for i = 1:length(funcs)
  cmd = sprintf('mex -g -v %s -DMATLAB -I. %s %s mex-src/%s.c', def, ariaclink, arialink, funcs{i});
  cmd
  eval(cmd)
end

%{
old script commands commented out

eval( ['mex -g ' def '-DWIN32 -DMATLAB -I. -L. -lariac_vc10_x64 -L../lib64 -lAriaVC10 mex-src/aria_init.c'] )
mex -g -DWIN32 -DMATLAB -I. -L. -lariac_vc10_x64 -L../lib64 -lAriaVC10 mex-src/arrobot_connect.c
mex -g -DWIN32 -DMATLAB -I. -L. -lariac_vc10_x64 -L../lib64 -lAriaVC10 mex-src/arrobot_disconnect.c
mex -g -DWIN32 -DMATLAB -I. -L. -lariac_vc10_x64 -L../lib64 -lAriaVC10 mex-src/arloginfo.c
mex -g -DWIN32 -DMATLAB -I. -L. -lariac_vc10_x64 -L../lib64 -lAriaVC10 mex-src/arrobot_setvel.c
mex -g -DWIN32 -DMATLAB -I. -L. -lariac_vc10_x64 -L../lib64 -lAriaVC10 mex-src/arrobot_setrotvel.c
mex -g -DWIN32 -DMATLAB -I. -L. -lariac_vc10_x64 -L../lib64 -lAriaVC10 mex-src/arrobot_getx.c
mex -g -DWIN32 -DMATLAB -I. -L. -lariac_vc10_x64 -L../lib64 -lAriaVC10 mex-src/arrobot_gety.c
mex -g -DWIN32 -DMATLAB -I. -L. -lariac_vc10_x64 -L../lib64 -lAriaVC10 mex-src/arrobot_getth.c
mex -g -DWIN32 -DMATLAB -I. -L. -lariac_vc10_x64 -L../lib64 -lAriaVC10 mex-src/arrobot_stop.c

%}
