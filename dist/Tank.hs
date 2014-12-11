#!/usr/bin/env runhaskell
{-# LANGUAGE TemplateHaskell #-}

module Main where
import Control.Applicative
import qualified Data.Text as T
import System.Process (system)
import System.Exit (exitFailure)
import System.IO (hPutStrLn, stderr)
import System.FilePath.Manip (modifyInPlace)
import Data.FileEmbed (embedDir)
import Control.Monad (void)
import qualified System.Directory as Dir
import qualified Data.ByteString.Char8 as BS

main :: IO ()
main = do
    projectName <- input "What is the name of your project? "
    makeDirectories projectName
    installTank projectName
    initProject projectName

exit :: String -> String -> IO ()
exit projectName err = do
    hPutStrLn stderr err
    Dir.setCurrentDirectory ".."
    Dir.removeDirectoryRecursive projectName
    exitFailure

input :: String -> IO String
input putstr = putStrLn putstr *> getLine

makeDirectories :: String -> IO ()
makeDirectories projectName = do
    Dir.createDirectory projectName 
    Dir.setCurrentDirectory projectName
    Dir.createDirectory "src"
    Dir.createDirectory "assets"
    Dir.createDirectory "build"

installTank :: String -> IO ()
installTank projectName = Dir.findExecutable "git" >>= \x -> case x of
    -- Git not found
    Nothing -> exit projectName "Cannot find git" 
    -- Git found
    _ -> mapM_ system ["git init",
                       "git submodule add https://github.com/qualiaa/Tank.git"]

replace :: String -> String -> String -> String
replace s old new = T.unpack $ T.replace (T.pack s) (T.pack old) (T.pack new)

fileReplace :: String -> String -> FilePath -> IO()
fileReplace s1 s2 = modifyInPlace (replace s1 s2) 

initProject :: String -> IO ()
initProject projectName = do
    mapM_ (uncurry BS.writeFile) $(embedDir "templates")
    fileReplace "<project_name>" projectName "CMakeLists.txt"
    void $ system "git commit -m \"Initial commit.\" -a"
