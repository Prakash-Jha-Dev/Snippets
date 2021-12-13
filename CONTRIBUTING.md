# Before creating a new PR
Please create an issue and tag it with any of belowe listed tags before creating a PR.
  * Feature 
  * Bug 
  * Documentation 
  * Test

Maintainer shall review the issue and assign it, after this you can submit a PR.
(It saves effort of both maintainer and contributor by avoiding unnecessary contribution)

## Creating a PR to add new Algorithm or Data Structure 
Submit one PR for one Algorithm or one Data Structure. When adding a new Algo or DS, 
make sure to add a test file as well showing the way to use the given Algo or DS.

Please re-use existing code intsead of adding your own implementation.

This project uses ICIE plugin for VS Code (https://github.com/pustaczek/icie), when adding 
new file, please use defined fields (Name, Description, Detail, Guarantee, Dependencies).
- filename: small case, words seperated by _ instead of space
- Name: FileName in CapitalCamelCase
- Description : Description of algorithm or data structure 
- Detail: Tags to identify field and related field of algo or ds
- Guarantee: End delimiter of code. (e.g. This project uses "// Name". Look at end of any file in c++ folder for example)
- Dependency: filename of other files required for this code (Reusing code instead of implementing it again)

Please don't make PR with adhoc algorithms.

## Creating a PR for Test
Test file should have same name as filename for which test is written. Test file should use the use case of algorithm and ds.

## Creating a PR for Bug fix or Documentation 
Make appropriate changes and submit it.


Note: The project is only for c++ 
