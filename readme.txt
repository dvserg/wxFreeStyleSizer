/***************************************************************
 * Name:      Readme.txt
 * Purpose:   Readme file
 * Author:    Sergey Dvoryantsev
 * Created:   2019-09-19
 * Copyright: (c) Sergey Dvoryantsev
 * License:
 **************************************************************/

Class wxFreeStyleSizer
This class is a Sizer implementation for the wxWidgets project.
The behavior of this Sizer is reminiscent of the standard behavior of Delphi forms and panels.


Feature description:

- Each control placed on the sorter can be aligned in one of the sides (left/right/top/bottom/center).
  Alignment is made about the entire width of the side.

- For each control located on the sorter, either side can be fixed in the current position relative
  to the side of the sizer. When resizing the sizer, this pinned position will remain.
  This behavior eliminates the use of alignment.

- Each control placed on the sizer can have a splitter that allows you to change its size. But this
  does not affect the parties to the element that participate in the alignment.
  For an anchor, this works.

Aligns:
- You can define one of the left/right/top/bottom/center(all client). The control will be placed on the entire size
  of the selected side, or it will stretch to the entire free space of the sizer.
- Àlignment works on the mechanism of anchors, and uses two adjacent sides with the selected direction
  of alignment. Therefore, when aligning, the splitter is only available on the side opposite the
  direction of alignment.
- Àlignment and anchors do not work at the same time.
- Alignment in the presence of several controls has the following priority:
  Top/Bottom - the first;
  Left/Right - the second;
  Center(all client) - last of all.
- Anchors do not participate in priority, and can be located on the sizer as is - regardless of aligns.
- Ñontrols aligned in directions are grouped into stacks in the order they are added to the sizer.

Splitters:
- You can change the style of the splitter
- You can change the type of drag tracker.


Constraints:

- Alignment and anchors do not work together (but this is one and the same mechanism).
- Splitters do not work on the sides for which alignment is defined.

Known problem:
- The fast movement of the tracker causes it to flicker.

Note:

The project was developed on codeblocks in Windows, and was not optimized for other OS.
The project was not designed for commercial use.
The project is provided as is without any obligation on the part of the author.
All copyrights to the basic source code are reserved.
No licenses have been added for this project at this time.
All rights to the code of other copyright holders used in this project are retained in full.
It is allowed to use this code for cases not related to commercial activity.
